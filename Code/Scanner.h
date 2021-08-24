#pragma once

#include <string>
#include "Token.h"

class Scanner
{
public:
    Tokens ScanTokens(const std::string& source);

private:
    Token MakeToken(const TokenType type, const char* sourceStart, const char* sourceEnd);
};