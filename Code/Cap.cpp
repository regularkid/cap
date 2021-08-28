#include "Cap.h"
#include "Utils.h"

// ----------------------------------------------------------------------------
void Cap::Run(const std::string& source)
{
    // Scan tokens
    m_scanner.ScanTokens(source);
    PrintTokens(m_scanner.GetTokens());
    if (m_scanner.Error())
    {
        return;
    }

    // Generate bytecode

    // Interpret
}