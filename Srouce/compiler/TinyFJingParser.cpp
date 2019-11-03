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
            return ParseBinaryOpRHS(reading, end, std::move(lhs), -1);
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
                    op = UnaryOperator::NOT;
                    break;
                case CodeTokenType::Add:
                    op = UnaryOperator::ADD;
                    break;
                case CodeTokenType::Sub:
                    op = UnaryOperator::SUB;
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

        ast::BaseAst::Ptr
        Parser::Expression::ParseBinaryOpRHS(Parser::Iterator &reading, Parser::Iterator &end,
                ast::BaseAst::Ptr lhs, int precedence) {
            while (reading != end) {

            }
            return nullptr;
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
            return nullptr;
        }


    }

}
