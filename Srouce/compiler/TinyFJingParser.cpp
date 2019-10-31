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
                    break;
                case CodeTokenType::Float:
                    break;
                case CodeTokenType::Double:
                    break;
                case CodeTokenType::Identifier:
                    break;
                case CodeTokenType::False:
                    break;
                case CodeTokenType::True:
                    break;
                case CodeTokenType::LeftParen:
                    break;
                case CodeTokenType::RightParen:
                    break;
                case CodeTokenType::Add:
                    break;
                case CodeTokenType::Sub:
                    break;
                case CodeTokenType::Not:
                    break;
                default:
                    break;
            }
            return nullptr;
        }


        ast::BaseAst::Ptr
        Parser::Expression::ParseExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            return nullptr;
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseNumberExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            using namespace value;
            using namespace ast;
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            BaseValue::Ptr node = nullptr;
            switch (reading->tokenType) {
                case CodeTokenType::Integer:
                    node = std::make_shared<IntegerValue>(reading->data.int_value);
                    break;
                case CodeTokenType::Float:
                    node = std::make_shared<FloatValue>(reading->data.float_value);
                    break;
                case CodeTokenType::Double:
                    node = std::make_shared<DoubleValue>(reading->data.double_value);
                    break;
                default:
                    throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            reading++;
            return std::make_shared<NumberExpressionAst>(std::move(node));
        }

        ast::BaseAst::Ptr
        Parser::Expression::ParseUnaryExpression(Parser::Iterator &reading, Parser::Iterator &end) {
            if (reading == end) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ENDED")));
            }
            CodeTokenType tokenType = reading->tokenType;
            if (tokenType != CodeTokenType::Not && tokenType != CodeTokenType::Add
                && tokenType != CodeTokenType::Sub) {
                throw std::runtime_error(GetFormatMsg(T("TOKEN_ERROR")));
            }
            // todo
            return nullptr;
        }
    }

}
