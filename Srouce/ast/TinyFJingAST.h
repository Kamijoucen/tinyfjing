#ifndef TINYFJING_TINYFJINGAST_H
#define TINYFJING_TINYFJINGAST_H

#include "TinyFJingSTL.h"
#include "TinyFJingValue.h"

namespace tinyfjing {

    namespace ast {

        enum class BinaryOperator {
            Add,
            Sub,
            Div,
            Mul,
            Mod,
            And,
            Or,
            LT,
            GT,
            LE,
            GE,
            EQ,
            NE,
            ERROR
        };

        enum class UnaryOperator {
            Add,
            Sub,
            Not,
            ERROR
        };

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

            BinaryExpressionAst(BinaryOperator op, BaseAst::Ptr left, BaseAst::Ptr right);

            BinaryOperator op;
            BaseAst::Ptr left;
            BaseAst::Ptr right;
        };

        class UnaryExpressionAst : public BaseAst {
        public:
            typedef std::shared_ptr<UnaryExpressionAst> Ptr;
            typedef std::weak_ptr<BinaryExpressionAst> WeakPtr;

            ValuePtr eval() override;

            UnaryExpressionAst(UnaryOperator op, BaseAst::Ptr ptr);

            UnaryOperator op;
            BaseAst::Ptr ptr;
        };

        class UsingStatementAst : public BaseAst {
        public:
            typedef std::shared_ptr<UsingStatementAst> Ptr;
            typedef std::weak_ptr<UsingStatementAst> WeakPtr;

            ValuePtr eval() override;

            std::vector<string_t> usings;
        };

        class NameAst : public BaseAst {
        public:
            typedef std::shared_ptr<NameAst> Ptr;
            typedef std::weak_ptr<NameAst> WeakPtr;

            ValuePtr eval() override;

            explicit NameAst(string_t name);

            string_t name;
        };

        class FunctionCallAst : public BaseAst {
        public:
            typedef std::shared_ptr<FunctionCallAst> Ptr;
            typedef std::weak_ptr<FunctionCallAst> WeakPtr;

            ValuePtr eval() override;

            FunctionCallAst(string_t callName, std::vector<BaseAst::Ptr> args);

            string_t callName;
            std::vector<BaseAst::Ptr> args;
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
