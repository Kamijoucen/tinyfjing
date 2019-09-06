#ifndef TINYFJING_TINYFJINGAST_H
#define TINYFJING_TINYFJINGAST_H

#include "TinyFJingSTL.h"

namespace tinyfjing {

    namespace ast {

        class BaseAst : public std::enable_shared_from_this<BaseAst> {
        public:
            typedef std::shared_ptr<BaseAst> Ptr;
            typedef std::weak_ptr<BaseAst> WeakPtr;

            virtual void eval() = 0;

            virtual ~BaseAst() = 0;
        };

        class UsingStatementAst : public BaseAst {
        public:
            typedef std::shared_ptr<UsingStatementAst> Ptr;
            typedef std::weak_ptr<UsingStatementAst> WeakPtr;

            std::vector<string_t> usings;

            void eval() override;

            ~UsingStatementAst() override = default;
        };

        class IfStatementAst : public BaseAst {
        public:
            typedef std::shared_ptr<IfStatementAst> Ptr;
            typedef std::weak_ptr<IfStatementAst> WeakPtr;

            void eval() override;

            BaseAst::Ptr condition;
            std::vector<BaseAst::Ptr> ifBody;


            ~IfStatementAst() override = default;
        };

    }

}


#endif //TINYFJING_TINYFJINGAST_H
