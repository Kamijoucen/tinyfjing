#include "TinyFJingParser.h"

#include <stdexcept>
#include "TinyFJingMessage.h"
#include "TinyFJingLexical.h"

namespace tinyfjing {

    namespace compiler {

        Module::Ptr Module::Parse(const CodeFile::Ptr &file) {
            if (file->tokens.begin() == file->tokens.end()) {
                return nullptr;
            }
            Module::Ptr ptr = std::make_shared<Module>();

            auto reading = file->tokens.begin();
            auto end = file->tokens.end();
            if (reading->tokenType != CodeTokenType::Module) {
                throw std::runtime_error(GetFormatMsg(T("FIRST_LINE_NEED_MODULE")));
            }
            reading++;

            if (reading->tokenType != CodeTokenType::Identifier) {
                throw std::runtime_error(GetFormatMsg(T("NEED_IDENTIFIER")));
            }
            ptr->name = reading->str;
            reading++;


            while (reading != end) {
                switch (reading->tokenType) {
                    case CodeTokenType::Using: {
                        auto usingNode = Parser::Statement::ParseUsingStatement(reading, end);
                        ptr->usings.push_back(std::move(usingNode));
                        break;
                    }
                    case CodeTokenType::Var: {
                        break;
                    }
                    case CodeTokenType::Identifier: {
                        // 语句第一行出现Identifier通常是变量赋值，函数调用
                        auto identNode = Parser::Expression::ParseIdentifierExpression(reading, end);
                        ptr->codes.push_back(std::move(identNode));
                        break;
                    }
                    case CodeTokenType::If: {
                        auto ifNode = Parser::Statement::ParseIfStatement(reading, end);
                        ptr->codes.push_back(std::move(ifNode));
                        break;
                    }
                    case CodeTokenType::While: {
                        break;
                    }
                    default:
                        break;
                }
            }

            return ptr;
        }


        ast::UsingStatementAst::Ptr
        Parser::Statement::ParseUsingStatement(Parser::Iterator &reading, Parser::Iterator &end) {
            using namespace ast;
            UsingStatementAst::Ptr ptr = std::shared_ptr<UsingStatementAst>();

            if (reading->tokenType != CodeTokenType::Using) {
                throw std::runtime_error(GetFormatMsg(T("NEED_KEYWORD"), {{T("name"), T("using")}}));
            }
            reading++;

            if (reading != end && reading->tokenType != CodeTokenType::Identifier) {
                throw std::runtime_error(GetFormatMsg(T("NEED_IDENTIFIER")));
            }
            ptr->usings.push_back(reading->str);
            reading++;

            while (reading != end && reading->tokenType == CodeTokenType::Comma) {
                reading++; // eat ,
                if (reading == end) {
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
                }
                if (reading->tokenType == CodeTokenType::Identifier) {
                    ptr->usings.push_back(reading->str);
                    reading++;
                }
            }
            return ptr;
        }

        ast::IfStatementAst::Ptr
        Parser::Statement::ParseIfStatement(Parser::Iterator &reading, Parser::Iterator &end) {
            return nullptr;
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParsePrimaryExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            switch (reading->tokenType) {
                case CodeTokenType::Integer:
                case CodeTokenType::Float:
                case CodeTokenType::Double:
                    return ParseNumberExpression(reading, end);
                case CodeTokenType::Identifier:
                    return ParseIdentifierExpression(reading, end);
                case CodeTokenType::False:
                case CodeTokenType::True:
                    return ParseBooleanExpression(reading, end);
                case CodeTokenType::LeftParen:
                    return ParseParenExpression(reading, end);
                case CodeTokenType::Add:
                case CodeTokenType::Sub:
                case CodeTokenType::Not:
                    return ParseUnaryExpression(reading, end);
                default:
                    // todo 这里可以抛出异常
                    break;
            }
            return nullptr;
        }


        ast::BaseAst::Ptr
        Parser::Expression::ParseExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            // 将二元表达式 1+2*3 拆分成 1, +2, *3 来解析
            // ParsePrimaryExpression将解析第一个表达式 1
            auto lhs = ParsePrimaryExpression(reading, end);
            if (lhs == nullptr) {
                return nullptr;
            }
            // 这里的 precedence 参数表示当前方法能处理的最低优先级，低于此优先级将直接返回
            return ParseBinaryOpRHS(reading, end, std::move(lhs), 0);
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseNumberExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            using namespace value;
            using namespace ast;
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            BaseValue::Ptr value = nullptr;
            switch (reading->tokenType) {
                case CodeTokenType::Integer:
                    value = std::make_shared<IntegerValue>(reading->data.int_value);
                    break;
                case CodeTokenType::Float:
                    value = std::make_shared<FloatValue>(reading->data.float_value);
                    break;
                case CodeTokenType::Double:
                    value = std::make_shared<DoubleValue>(reading->data.double_value);
                    break;
                default:
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            reading++;
            return std::make_shared<NumberExpressionAst>(std::move(value));
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseBooleanExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            using namespace value;
            using namespace ast;
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            std::shared_ptr<BooleanValue> value = nullptr;
            switch (reading->tokenType) {
                case CodeTokenType::True:
                    value = std::make_shared<BooleanValue>(true);
                    break;
                case CodeTokenType::False:
                    value = std::make_shared<BooleanValue>(false);
                    break;
                default:
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            reading++;
            return std::make_shared<BooleanExpressionAst>(std::move(value));
        }


        ast::BaseAst::Ptr
        Parser::Expression::ParseUnaryExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            using namespace ast;
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            CodeTokenType opTokenType = reading->tokenType;
            UnaryOperator op;
            switch (opTokenType) {
                case CodeTokenType::Not:
                    op = UnaryOperator::Not;
                    break;
                case CodeTokenType::Add:
                    op = UnaryOperator::Add;
                    break;
                case CodeTokenType::Sub:
                    op = UnaryOperator::Sub;
                    break;
                default:
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            reading++;
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            // 单目运算符可以支持的运算: f ident, f (exp), f value
            // 单目运算符的优先级最高，所以不必考虑单目运算符作用于二元表达式的情况
            BaseAst::Ptr unaryExpNode = nullptr;
            // todo 这里可以做一下类型检查，例如 not 运算符不能作用于数字
            switch (reading->tokenType) {
                case CodeTokenType::Integer:
                case CodeTokenType::Float:
                case CodeTokenType::Double:
                    unaryExpNode = ParseNumberExpression(reading, end);
                    break;
                case CodeTokenType::Identifier:
                    unaryExpNode = ParseIdentifierExpression(reading, end);
                    break;
                case CodeTokenType::False:
                case CodeTokenType::True:
                    unaryExpNode = ParseBooleanExpression(reading, end);
                    break;
                case CodeTokenType::LeftParen:
                    unaryExpNode = ParseParenExpression(reading, end);
                    break;
                default:
                    throw std::runtime_error(GetFormatMsg("TOKEN_ERROR"));
            }
            return std::make_shared<UnaryExpressionAst>(op, std::move(unaryExpNode));
        }

        inline int GetOperatorPrecedence(CodeTokenType op) {
            // 优先级表
            static std::map<CodeTokenType, int> PRECEDENCE_TABLE = {
                    {CodeTokenType::Add, 10},
                    {CodeTokenType::Sub, 10},
                    {CodeTokenType::Mul, 20},
                    {CodeTokenType::Div, 20},
                    {CodeTokenType::Mod, 20},
                    {CodeTokenType::And, 30},
                    {CodeTokenType::Or,  30},
                    {CodeTokenType::EQ,  5},
                    {CodeTokenType::LT,  5},
                    {CodeTokenType::GT,  5},
                    {CodeTokenType::LE,  5},
                    {CodeTokenType::GE,  5},
                    {CodeTokenType::NE,  5},

            };
            auto iter = PRECEDENCE_TABLE.find(op);
            if (iter == PRECEDENCE_TABLE.end()) {
                return -1;
            }
            return iter->second;
        }

        inline ast::BinaryOperator GetBinaryOpByCodeTokenType(const CodeTokenType &type) {
            using namespace ast;
            switch (type) {
                case CodeTokenType::Add:
                    return BinaryOperator::Add;
                case CodeTokenType::Sub:
                    return BinaryOperator::Sub;
                case CodeTokenType::Mul:
                    return BinaryOperator::Mul;
                case CodeTokenType::Div:
                case CodeTokenType::IntDiv:
                    return BinaryOperator::Div;
                case CodeTokenType::Mod:
                    return BinaryOperator::Mod;
                case CodeTokenType::LT:
                    return BinaryOperator::LT;
                case CodeTokenType::GT:
                    return BinaryOperator::GT;
                case CodeTokenType::LE:
                    return BinaryOperator::LE;
                case CodeTokenType::GE:
                    return BinaryOperator::GE;
                case CodeTokenType::EQ:
                    return BinaryOperator::EQ;
                case CodeTokenType::NE:
                    return BinaryOperator::NE;
                case CodeTokenType::And:
                    return BinaryOperator::And;
                case CodeTokenType::Or:
                    return BinaryOperator::Or;
                default:
                    return BinaryOperator::ERROR;
            }
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseBinaryOpRHS(Parser::Iterator &reading, Parser::Iterator &end,
                                             ast::BaseAst::Ptr lhs, int precedence) {
            using namespace ast;
            while (true) {
                // 当前的运算符
                CodeTokenType curOp = reading->tokenType;
                int curOpPrecedence = GetOperatorPrecedence(curOp);
                if (precedence > curOpPrecedence) {
                    return lhs;
                }
                reading++; // eat op
                BaseAst::Ptr rhs = ParsePrimaryExpression(reading, end);

                CodeTokenType nextOp = reading->tokenType;
                int nextOpPrecedence = GetOperatorPrecedence(nextOp);
                if (nextOpPrecedence > curOpPrecedence) {
                    rhs = ParseBinaryOpRHS(reading, end, std::move(rhs), curOpPrecedence + 1);
                    if (rhs == nullptr) {
                        return nullptr;
                    }
                }
                BinaryOperator curBinOp = GetBinaryOpByCodeTokenType(curOp);
                if (curBinOp == BinaryOperator::ERROR) {
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
                }
                lhs = std::make_shared<BinaryExpressionAst>(curBinOp, std::move(lhs), std::move(rhs));
            }
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseParenExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            if (reading->tokenType != CodeTokenType::LeftParen) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            reading++; // eat (
            auto exp = ParseExpression(reading, end);
            if (exp == nullptr) {
                throw std::runtime_error(GetFormatMsg(T("EXPRESSION_NOT_FOUND")));
            }
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            if (reading->tokenType != CodeTokenType::RightParen) {
                // todo 添加完整的错误描述
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            reading++; // eat )
            return exp;
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseIdentifierExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            if (reading == end || reading->tokenType != CodeTokenType::Identifier) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            string_t name = reading->str;
            reading++; // eat ident
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            // 标识符存在 ident, ident=, ident( 。三种情况
            if (reading->tokenType == CodeTokenType::LeftParen) {
                reading++; // eat (
                std::vector<ast::BaseAst::Ptr> args;
                while (reading != end && reading->tokenType != CodeTokenType::RightParen) {
                    auto arg = Parser::Expression::ParseExpression(reading, end);
                    if (arg == nullptr) {
                        throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
                    }
                    args.push_back(std::move(arg));
                }
                if (reading->tokenType != CodeTokenType::RightParen) {
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
                }
                reading++; // eat )
                return std::make_shared<ast::FunctionCallAst>(std::move(name), std::move(args));
            } else if (reading->tokenType == CodeTokenType::Assign) {
                reading++; // eat =
                if (reading == end) {
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
                }
                auto exp = Parser::Expression::ParseExpression(reading, end);
                if (exp == nullptr) {
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
                }

                return nullptr;
            } else {
                return std::make_shared<ast::NameAst>(std::move(name));
            }
        }


    }

}
