#pragma once

#include <string>
#include "Token.h"

class Scanner
{
public:
    Tokens ScanTokens(const std::string& source);
    bool Error() const;

private:
    Token MakeToken(const TokenType type, const char* sourceStart, const char* sourceEnd, const int line);

    bool m_error = false;
};