#pragma once

#include <string>
#include "Token.h"

class Scanner
{
public:
    void ScanTokens(const std::string& source);
    const Tokens& GetTokens() { return m_tokens; }
    bool Error() const;

private:
    bool ScanWhitespace();
    bool ScanComment();
    bool ScanSymbolKeyword();
    bool ScanNumber();
    bool ScanString();
    bool ScanIdentifier();
    Token MakeToken(const TokenType type, const char* sourceStart, const char* sourceEnd, const int line);

    Tokens m_tokens;
    bool m_error = false;

    const char* m_sourceCur = nullptr;
    const char* m_sourceEnd = nullptr;
    int m_line = -1;
};