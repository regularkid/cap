#pragma once

#include <stack>
#include "Bytecode.h"
#include "Ops.h"
#include "Value.h"

class Runtime
{
public:
    void Execute(const Bytecode* code);

private:
    inline Byte ReadByte();

    void ExecutePush();
    void ExecutePop();
    void ExecutePrint();
    void ExecuteAdd();
    void ExecuteSubtract();
    void ExecuteMultiply();
    void ExecuteDivide();

    bool m_error = false;

    const Bytecode* m_code;
    const Byte* m_ip = nullptr;
    Op m_curOp = Op::None;
    std::vector<Value> m_stack;
};