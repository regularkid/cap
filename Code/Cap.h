#pragma once

#include <string>
#include "Compiler.h"
#include "Runtime.h"

class Cap
{
public:
    void Run(const std::string& source);

private:
    Compiler m_compiler;
    Runtime m_runtime;
};