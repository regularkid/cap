#include "Scanner.h"

Tokens Scanner::ScanTokens(const std::string& source)
{
    Tokens tokens;

    // Scan...
    
    // Debug/Test
    Token t1;
    t1.m_type = TokenType::Plus;
    tokens.push_back(t1);

    Token t2;
    t2.m_type = TokenType::String;
    t2.m_sourceStart = "Test";
    t2.m_sourceEnd = t2.m_sourceStart + 4;
    tokens.push_back(t2);

    Token t3;
    t3.m_type = TokenType::EndOfFile;
    tokens.push_back(t3);

    return tokens;
}