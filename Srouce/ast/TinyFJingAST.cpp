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

        ValuePtr
        NumberExpressionAst::eval() {
            return nullptr;
        }
        NumberExpressionAst::NumberExpressionAst(ValuePtr value) : value(std::move(value)) {}
    }

}
