#include <functional>
#include <unordered_map>
#include "Runtime.h"
#include "Ops.h"
#include "Utils.h"

#define DEBUG_RUNTIME

#define RUNTIME_ERROR(s, ...) LOG("[Runtime Error] "##s, __VA_ARGS__); printf("\n"); m_error = true;

void Runtime::Execute(const Executable* executable)
{
    if (!executable)
    {
        LOG("Unable to execute: Invalid executable");
        return;
    }

    m_executable = executable;
    m_ip = &(m_executable->m_code[0]);

    bool done = false;
    while (!done)
    {
#ifdef DEBUG_RUNTIME
        LOG("---------- Begin Trace ----------");
        LOG("Stack:");
        for (const Value& value : m_stack)
        {
            LOG("%s", ValueToString(value).c_str());
        }

        LOG("Op:");
        LOG("%s", ExecutableOpToString(m_ip).c_str());
        LOG("---------- End Trace ------------");
#endif

        m_curOp = static_cast<Op>(ReadByte());
        switch (m_curOp)
        {
            case Op::End: done = true;  break;
            case Op::Constant: ExecuteConstant(); break;
            case Op::Negate: ExecuteNegate(); break;
            case Op::Push: ExecutePush(); break;
            case Op::Pop: ExecutePop(); break;
            case Op::Print: ExecutePrint(); break;
            case Op::Add: ExecuteAdd(); break;
            case Op::Subtract: ExecuteSubtract(); break;
            case Op::Multiply: ExecuteMultiply(); break;
            case Op::Divide: ExecuteDivide(); break;
        }

        if (m_error)
        {
            break;
        }
    }
}

Byte Runtime::ReadByte()
{
    return *m_ip++;
}

void Runtime::ExecuteConstant()
{
    const int constantIdx = ReadByte();
    const Value& value = m_executable->m_constants[constantIdx];
    m_stack.push_back(value);
}

void Runtime::ExecuteNegate()
{
    Value value = m_stack.back();
    m_stack.pop_back();

    if (value.m_type != ValueType::Number)
    {
        RUNTIME_ERROR("Can only negate number values");
    }
    else
    {
        value.as.number = -value.as.number;
        m_stack.push_back(value);
    }
}

void Runtime::ExecutePush()
{
    m_stack.push_back(Value(static_cast<float>(ReadByte())));
}

void Runtime::ExecutePop()
{
    m_stack.pop_back();
}

void Runtime::ExecutePrint()
{
    LOG("Stack Value: %.02f", m_stack.back().as.number);
}

void Runtime::ExecuteAdd()
{
    Value b = m_stack.back();
    m_stack.pop_back();
    Value a = m_stack.back();
    m_stack.pop_back();

    if (a.m_type == ValueType::Number && b.m_type == ValueType::Number)
    {
        m_stack.push_back(a.as.number + b.as.number);
    }
    else
    {
        RUNTIME_ERROR("Unable to add non-number types: %s + %s", ValueToString(a).c_str(), ValueToString(b).c_str());
    }
}

void Runtime::ExecuteSubtract()
{
    Value b = m_stack.back();
    m_stack.pop_back();
    Value a = m_stack.back();
    m_stack.pop_back();

    if (a.m_type == ValueType::Number && b.m_type == ValueType::Number)
    {
        m_stack.push_back(a.as.number - b.as.number);
    }
    else
    {
        RUNTIME_ERROR("Unable to subtract non-number types: %s - %s", ValueToString(a).c_str(), ValueToString(b).c_str());
    }
}

void Runtime::ExecuteMultiply()
{
    Value b = m_stack.back();
    m_stack.pop_back();
    Value a = m_stack.back();
    m_stack.pop_back();

    if (a.m_type == ValueType::Number && b.m_type == ValueType::Number)
    {
        m_stack.push_back(a.as.number * b.as.number);
    }
    else
    {
        RUNTIME_ERROR("Unable to multiply non-number types: %s * %s", ValueToString(a).c_str(), ValueToString(b).c_str());
    }
}

void Runtime::ExecuteDivide()
{
    Value b = m_stack.back();
    m_stack.pop_back();
    Value a = m_stack.back();
    m_stack.pop_back();

    if (a.m_type == ValueType::Number && b.m_type == ValueType::Number)
    {
        if (b.as.number != 0.0f)
        {
            m_stack.push_back(a.as.number / b.as.number);
        }
        else
        {
            RUNTIME_ERROR("Divide by zero: %s / %s", ValueToString(a).c_str(), ValueToString(b).c_str());
        }
    }
    else
    {
        RUNTIME_ERROR("Unable to divide non-number types: %s / %s", ValueToString(a).c_str(), ValueToString(b).c_str());
    }
}