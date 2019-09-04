#include "TinyFJingParser.h"

#include <stdexcept>
#include "Message.h"

namespace tinyfjing {

    namespace compiler {

        Module::Ptr Module::Parse(const CodeFile::Ptr &file) {
            if (file->tokens.begin() == file->tokens.end()) {
                return nullptr;
            }
            Module::Ptr ptr = std::make_shared<Module>();

            auto reading = file->tokens.begin();
            if (reading->tokenType != CodeTokenType::Module) {
                throw std::runtime_error(FIRST_LINE_NEED_MODULE);
            }
            reading++;

            if (reading->tokenType != CodeTokenType::Identifier) {
                throw std::runtime_error(NEED_IDENTIFIER);
            }
            ptr->name = reading->str;
            reading++;


            while (reading != file->tokens.end()) {
//                switch () {}
            }

            return nullptr;
        }
    }

}
