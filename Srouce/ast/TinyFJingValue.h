#ifndef TINYFJING_TINYFJINGVALUE_H
#define TINYFJING_TINYFJINGVALUE_H

#include "TinyFJingSTL.h"

namespace tinyfjing {

    namespace value {

        enum class ValueType {
            Integer,
            Float,
            String,
            UnKnow
        };

        class BaseValue {
        public:
            typedef std::shared_ptr<BaseValue> Ptr;
            typedef std::weak_ptr<BaseValue> WeakPtr;

            virtual ValueType GetType() = 0;
            virtual ~BaseValue() = default;
        };

        class IntegerValue : public BaseValue {
        public:
            ValueType GetType() override;

            int value;

            explicit IntegerValue(int value);
        };

        class FloatValue : public BaseValue {
        public:
            ValueType GetType() override;

            float value;

            explicit FloatValue(float value);
        };


    }

}


#endif //TINYFJING_TINYFJINGVALUE_H
