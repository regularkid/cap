#include <functional>
#include <unordered_map>
#include "VM.h"
#include "Ops.h"
#include "Utils.h"

void VM::Run(const Bytecode* code)
{
    m_code = code;
    m_ip = &((*m_code)[0]);

    bool done = false;
    while (!done)
    {
        const Op op = static_cast<Op>(ReadByte());
        switch (op)
        {
            case Op::End: done = true;  break;
            case Op::Push: ExecutePush(); break;
            case Op::Pop: ExecutePop(); break;
            case Op::Print: ExecutePrint(); break;
        }
    }
}

Byte VM::ReadByte()
{
    return *m_ip++;
}

void VM::ExecutePush()
{
    m_stack.push(Value(static_cast<float>(ReadByte())));
}

void VM::ExecutePop()
{
    m_stack.pop();
}

void VM::ExecutePrint()
{
    LOG("Stack Value: %.02f", m_stack.top().as.number);
}