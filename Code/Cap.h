#pragma once

#include <string>
#include "Runtime.h"
#include "Scanner.h"

class Cap
{
public:
    void Run(const std::string& source);

private:
    Scanner m_scanner;
    Runtime m_runtime;
};