#include "Compiler.h"
#include "Token.h"

//#define DEBUG_PRINT_TOKENS

void Compiler::Compile(const std::string& source)
{
    m_scanner.ScanTokens(source);
    if (m_scanner.Error())
    {
        m_error = true;
        return;
    }

#ifdef DEBUG_PRINT_TOKENS
    PrintTokens(m_scanner.GetTokens());
#endif
}