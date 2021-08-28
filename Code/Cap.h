#pragma once

#include <string>
#include "Scanner.h"
#include "VM.h"

class Cap
{
public:
    void Run(const std::string& source);

private:
    Scanner m_scanner;
    VM m_vm;
};