#include "TinyFJingParser.h"

#include <stdexcept>
#include "TinyFJingMessage.h"

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
                        auto usingNode = Parser::ParseUsingStatement(reading, end);
                        ptr->usings.push_back(std::move(usingNode));
                        break;
                    }
                    default:
                        break;
                }
            }

            return ptr;
        }


        ast::UsingStatementAst::Ptr
        Parser::ParseUsingStatement(Parser::Iterator &reading, Parser::Iterator &end) {
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
    }

}
