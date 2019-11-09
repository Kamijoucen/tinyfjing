/*
 * @Author: kamijoucen
 * @Date: 2019-10-30 22:09:22
 * @LastEditTime: 2019-11-09 19:38:56
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\ast\TinyFJingAST.cpp
 * @
 */
#include "TinyFJingAST.h"

#include <utility>

#include "TinyFJingValue.h"

namespace tinyfjing
{

namespace ast
{

ValuePtr
UsingStatementAst::eval()
{
    return nullptr;
}

ValuePtr
IfStatementAst::eval()
{
    return nullptr;
}

ValuePtr
BinaryExpressionAst::eval()
{

    return nullptr;
}

BinaryExpressionAst::BinaryExpressionAst(BinaryOperator op, BaseAst::Ptr left, BaseAst::Ptr right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

ValuePtr
NumberExpressionAst::eval()
{
    return value;
}

NumberExpressionAst::NumberExpressionAst(ValuePtr value) : value(std::move(value)) {}

ValuePtr BooleanExpressionAst::eval()
{
    return nullptr;
}

BooleanExpressionAst::BooleanExpressionAst(ValuePtr value) : value(std::move(value)) {}

ValuePtr UnaryExpressionAst::eval()
{
    return nullptr;
}

UnaryExpressionAst::UnaryExpressionAst(UnaryOperator op, BaseAst::Ptr ptr) : op(op), ptr(std::move(ptr)) {}

ValuePtr FunctionCallAst::eval()
{
    return nullptr;
}

FunctionCallAst::FunctionCallAst(string_t callName, std::vector<BaseAst::Ptr> args) : callName(std::move(callName)), args(std::move(args)) {}

ValuePtr NameAst::eval()
{
    return nullptr;
}

NameAst::NameAst(string_t name) : name(std::move(name)) {}
} // namespace ast

} // namespace tinyfjing
