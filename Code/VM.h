#pragma once

#include <stack>
#include "Bytecode.h"
#include "Value.h"

class VM
{
public:
    void Run(const Bytecode* code);

private:
    inline Byte ReadByte();

    void ExecutePush();
    void ExecutePop();
    void ExecutePrint();

    const Bytecode* m_code;
    const Byte* m_ip = nullptr;
    std::stack<Value> m_stack;
};