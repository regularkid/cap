#include <functional>
#include <unordered_map>
#include "Runtime.h"
#include "Ops.h"
#include "Utils.h"

#define DEBUG_RUNTIME

void Runtime::Execute(const Bytecode* code)
{
    m_code = code;
    m_ip = &((*m_code)[0]);

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
        LOG("%s", BytecodeOpToString(m_ip).c_str());
        LOG("---------- End Trace ------------");
#endif

        m_curOp = static_cast<Op>(ReadByte());
        switch (m_curOp)
        {
            case Op::End: done = true;  break;
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
        m_error = true;
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
        m_error = true;
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
        m_error = true;
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
            m_error = true;
        }
    }
    else
    {
        RUNTIME_ERROR("Unable to divide non-number types: %s / %s", ValueToString(a).c_str(), ValueToString(b).c_str());
        m_error = true;
    }
}