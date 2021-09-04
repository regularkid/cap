#include "Compiler.h"
#include "Token.h"

//#define DEBUG_COMPILER

void Compiler::Compile(const std::string& source)
{
    m_scanner.ScanTokens(source);
    if (m_scanner.Error())
    {
        m_error = true;
        return;
    }

#ifdef DEBUG_COMPILER
    PrintTokens(m_scanner.GetTokens());
#endif

    for (const Token& token : m_scanner.GetTokens())
    {

    }
}