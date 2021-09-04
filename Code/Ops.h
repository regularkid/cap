#pragma once

enum class Op
{
    None,
    End,

    Constant,
    Negate,
    Push,
    Pop,
    Print,

    Add,
    Subtract,
    Multiply,
    Divide,
};