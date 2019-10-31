#include "TinyFJingValue.h"

namespace tinyfjing {

    namespace value {

        ValueType IntegerValue::GetType() {
            return ValueType::Integer;
        }

        IntegerValue::IntegerValue(int value) : value(value) {}

        ValueType FloatValue::GetType() {
            return ValueType::Float;
        }

        FloatValue::FloatValue(float value) : value(value) {}

        ValueType DoubleValue::GetType() {
            return ValueType::Double;
        }

        DoubleValue::DoubleValue(double value) : value(value) {}

        ValueType BooleanValue::GetType() {
            return ValueType::Boolean;
        }

        BooleanValue::BooleanValue(bool value) : value(value) {}
    }

}
