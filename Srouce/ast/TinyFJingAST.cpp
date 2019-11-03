#include "TinyFJingAST.h"

#include <utility>

#include "TinyFJingValue.h"

namespace tinyfjing {

    namespace ast {

        ValuePtr
        UsingStatementAst::eval() {
            return nullptr;
        }

        ValuePtr
        IfStatementAst::eval() {
            return nullptr;
        }

        ValuePtr
        BinaryExpressionAst::eval() {
            return nullptr;
        }

        BinaryExpressionAst::BinaryExpressionAst(BinaryOperator op, BaseAst::Ptr left, BaseAst::Ptr right)
                : op(op), left(left), right(right) {}

        ValuePtr
        NumberExpressionAst::eval() {
            return nullptr;
        }
        NumberExpressionAst::NumberExpressionAst(ValuePtr value) : value(std::move(value)) {}

        ValuePtr BooleanExpressionAst::eval() {
            return nullptr;
        }

        BooleanExpressionAst::BooleanExpressionAst(ValuePtr value) : value(std::move(value)) {}

        ValuePtr UnaryExpressionAst::eval() {
            return nullptr;
        }

        UnaryExpressionAst::UnaryExpressionAst(UnaryOperator op, BaseAst::Ptr ptr) : op(op), ptr(std::move(ptr)) {}
    }

}
