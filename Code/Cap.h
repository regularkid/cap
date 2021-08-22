#pragma once

#include <string>
#include "Scanner.h"

class Cap
{
public:
    void Run(const std::string& source);

private:
    Scanner m_scanner;
};