/*
 * @Author: kamijoucen
 * @Date: 2019-10-31 20:37:49
 * @LastEditTime: 2019-11-09 19:38:02
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\ast\TinyFJingValue.cpp
 * @
 */
#include "TinyFJingValue.h"

namespace tinyfjing
{

namespace value
{

ValueType IntegerValue::GetType()
{
    return ValueType::Integer;
}

IntegerValue::IntegerValue(int value) : value(value) {}

ValueType FloatValue::GetType()
{
    return ValueType::Float;
}

FloatValue::FloatValue(float value) : value(value) {}

ValueType DoubleValue::GetType()
{
    return ValueType::Double;
}

DoubleValue::DoubleValue(double value) : value(value) {}

ValueType BooleanValue::GetType()
{
    return ValueType::Boolean;
}

BooleanValue::BooleanValue(bool value) : value(value) {}
} // namespace value

} // namespace tinyfjing
