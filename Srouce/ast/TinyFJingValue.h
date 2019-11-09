/*
 * @Author: kamijoucen
 * @Date: 2019-10-31 20:37:49
 * @LastEditTime: 2019-11-09 19:39:04
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\ast\TinyFJingValue.h
 * @
 */
#ifndef TINYFJING_TINYFJINGVALUE_H
#define TINYFJING_TINYFJINGVALUE_H

#include "TinyFJingSTL.h"

namespace tinyfjing
{

namespace value
{

enum class ValueType
{
    Integer,
    Float,
    Double,
    String,
    Boolean,
    UnKnow
};

class BaseValue
{
public:
    typedef std::shared_ptr<BaseValue> Ptr;
    typedef std::weak_ptr<BaseValue> WeakPtr;

    virtual ValueType GetType() = 0;
    virtual ~BaseValue() = default;
};

class IntegerValue : public BaseValue
{
public:
    ValueType GetType() override;

    int value;

    explicit IntegerValue(int value);
};

class FloatValue : public BaseValue
{
public:
    ValueType GetType() override;

    float value;

    explicit FloatValue(float value);
};

class DoubleValue : public BaseValue
{
public:
    ValueType GetType() override;

    double value;

    explicit DoubleValue(double value);
};

class BooleanValue : public BaseValue
{
public:
    ValueType GetType() override;

    bool value;

    explicit BooleanValue(bool value);
};

} // namespace value

} // namespace tinyfjing

#endif //TINYFJING_TINYFJINGVALUE_H
