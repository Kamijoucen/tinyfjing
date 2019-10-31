#ifndef TINYFJING_TINYFJINGAST_H
#define TINYFJING_TINYFJINGAST_H

#include "TinyFJingSTL.h"
#include "TinyFJingValue.h"

namespace tinyfjing {

    namespace ast {

        using ValuePtr = value::BaseValue::Ptr;

        class BaseAst : public std::enable_shared_from_this<BaseAst> {
        public:
            typedef std::shared_ptr<BaseAst> Ptr;
            typedef std::weak_ptr<BaseAst> WeakPtr;

            virtual ValuePtr eval() = 0;

            virtual ~BaseAst() = default;
        };

        class NumberExpressionAst : public BaseAst {
        public:
            typedef std::shared_ptr<NumberExpressionAst> Ptr;
            typedef std::weak_ptr<NumberExpressionAst> WeakPtr;

            ValuePtr value = nullptr;

            explicit NumberExpressionAst(ValuePtr value);

            ValuePtr eval() override;
        };

        class BooleanExpressionAst : public BaseAst {
        public:
            typedef std::shared_ptr<BooleanExpressionAst> Ptr;
            typedef std::weak_ptr<NumberExpressionAst> WeakPtr;

            ValuePtr value = nullptr;

            explicit BooleanExpressionAst(ValuePtr value);

            ValuePtr eval() override;
        };

        class BinaryExpressionAst : public BaseAst {
        public:
            typedef std::shared_ptr<BinaryExpressionAst> Ptr;
            typedef std::weak_ptr<BinaryExpressionAst> WeakPtr;

            ValuePtr eval() override;

            BaseAst::Ptr left;
            BaseAst::Ptr right;
            // todo op
        };

        class UsingStatementAst : public BaseAst {
        public:
            typedef std::shared_ptr<UsingStatementAst> Ptr;
            typedef std::weak_ptr<UsingStatementAst> WeakPtr;

            std::vector<string_t> usings;

            ValuePtr eval() override;
        };

        class IfStatementAst : public BaseAst {
        public:
            typedef std::shared_ptr<IfStatementAst> Ptr;
            typedef std::weak_ptr<IfStatementAst> WeakPtr;

            ValuePtr eval() override;

            BaseAst::Ptr condition;
            std::vector<BaseAst::Ptr> ifBody;
        };

    }

}


#endif //TINYFJING_TINYFJINGAST_H
