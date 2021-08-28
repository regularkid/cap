#pragma once

#include "Bytecode.h"

enum class Op
{
    None,
    End,

    Push,
    Pop,
    Print,

    Add,
    Subtract,
    Multiply,
    Divide,
};