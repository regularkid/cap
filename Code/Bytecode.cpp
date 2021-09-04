#include "Bytecode.h"
#include "Ops.h"
#include "Value.h"

std::string BytecodeOpToString(const Byte* ip)
{
    char strBuff[128];
    strBuff[0] = '\0';

    Op op = static_cast<Op>(*ip);
    switch (op)
    {
        case Op::End: snprintf(strBuff, sizeof(strBuff), "[End]"); break;
        case Op::Push:
        {
            // TEMP
            Value param = Value(static_cast<float>(*(++ip)));
            snprintf(strBuff, sizeof(strBuff), "[Push %s]", ValueToString(param).c_str());
        } break;

        case Op::Pop: snprintf(strBuff, sizeof(strBuff), "[Pop]"); break;
        case Op::Print: snprintf(strBuff, sizeof(strBuff), "[Print]"); break;
        case Op::Add: snprintf(strBuff, sizeof(strBuff), "[Add]"); break;
        case Op::Subtract: snprintf(strBuff, sizeof(strBuff), "[Subtract]"); break;
        case Op::Multiply: snprintf(strBuff, sizeof(strBuff), "[Multiply]"); break;
        case Op::Divide: snprintf(strBuff, sizeof(strBuff), "[Divide]"); break;
    }

    return strBuff;
}