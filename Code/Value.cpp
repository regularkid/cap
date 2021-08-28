#include "Value.h"

std::string ValueToString(const Value& value)
{
    char strBuff[128];
    strBuff[0] = '\0';

    switch (value.m_type)
    {
        case ValueType::Bool: snprintf(strBuff, sizeof(strBuff), "[Bool: %s ]", value.as.boolean ? "true" : "false"); break;
        case ValueType::Number: snprintf(strBuff, sizeof(strBuff), "[Number: %s ]", std::to_string(value.as.number).c_str()); break;
        case ValueType::Pointer: snprintf(strBuff, sizeof(strBuff), "[Pointer: * ]"); break;
    }

    return strBuff;
}