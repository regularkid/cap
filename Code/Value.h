#pragma once

#include <string>

enum class ValueType
{
    Bool,
    Number,
    Pointer,
};

union ValueUnion
{
    ValueUnion(bool val) : boolean(val) {}
    ValueUnion(float val) : number(val) {}
    ValueUnion(void* val) : ptr(val) {}

    bool boolean;
    float number;
    void* ptr;
};

struct Value
{
    Value(bool val) : m_type(ValueType::Bool), as(val) {}
    Value(float val) : m_type(ValueType::Number), as(val) {}
    Value(void* val) : m_type(ValueType::Pointer), as(val) {}

    ValueType m_type;
    ValueUnion as;
};

std::string ValueToString(const Value& value);