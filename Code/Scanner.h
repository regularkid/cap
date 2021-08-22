#pragma once

#include <string>
#include <vector>
#include "Token.h"

class Scanner
{
public:
    Tokens ScanTokens(const std::string& source);
};