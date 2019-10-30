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
    }

}
