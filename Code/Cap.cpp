#include "Cap.h"
#include "Utils.h"

// ----------------------------------------------------------------------------
void Cap::Run(const std::string& source)
{
    // Scan tokens
    Tokens tokens = m_scanner.ScanTokens(source);
    PrintTokens(tokens);

    // Generate bytecode

    // Interpret
}