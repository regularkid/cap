#pragma once

#include <string>
#include "Executable.h"
#include "Scanner.h"

class Compiler
{
public:
    void Compile(const std::string& source);
    bool Error() const { return m_error; }

    Executable& GetExecutable() { return m_executable; }    // TODO: Make constant

private:
    int AddConstant(const Token& token);

    bool m_error = false;
    Scanner m_scanner;
    Executable m_executable;
};