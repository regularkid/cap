#include <functional>
#include <unordered_map>
#include "Runtime.h"
#include "Ops.h"
#include "Utils.h"

void Runtime::Execute(const Bytecode* code)
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

Byte Runtime::ReadByte()
{
    return *m_ip++;
}

struct Box2
{
    union
    {
        int intr;
        struct
        {
            int  a;
            int  b;
            int  c;
            int  d;
        } s;
    };
};

void Runtime::ExecutePush()
{
    m_stack.push(Value(static_cast<float>(ReadByte())));
}

void Runtime::ExecutePop()
{
    m_stack.pop();
}

void Runtime::ExecutePrint()
{
    LOG("Stack Value: %.02f", m_stack.top().as.number);
}