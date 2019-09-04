#ifndef TINYFJING_TINYFJINGPARSER_H
#define TINYFJING_TINYFJINGPARSER_H

#include "TinyFJingSTL.h"
#include "TinyFJingLexical.h"
#include "ast/TinyFJingAST.h"

namespace tinyfjing {

    namespace compiler {

        class Module {
        public:
            typedef std::shared_ptr<Module> Ptr;
            typedef std::weak_ptr<Module> WeakPtr;

            string_t name;  // 模块名
            std::vector<string_t> usings; // 引用的其他模块

            static Module::Ptr Parse(const CodeFile::Ptr &ptr);
        };


        namespace parser {



        }

    }

}

#endif //TINYFJING_TINYFJINGPARSER_H
