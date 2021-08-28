#include "Cap.h"
#include "Ops.h"
#include "Utils.h"

// ----------------------------------------------------------------------------
void Cap::Run(const std::string& source)
{
    // Scan tokens
    m_scanner.ScanTokens(source);
    //PrintTokens(m_scanner.GetTokens());
    if (m_scanner.Error())
    {
        return;
    }

    // Generate bytecode
    Bytecode code;
    code.push_back(static_cast<Byte>(Op::Push));
    code.push_back(static_cast<Byte>(12));

    code.push_back(static_cast<Byte>(Op::Push));
    code.push_back(static_cast<Byte>(34));

    code.push_back(static_cast<Byte>(Op::Add));

    code.push_back(static_cast<Byte>(Op::Print));
    code.push_back(static_cast<Byte>(Op::Pop));

    code.push_back(static_cast<Byte>(Op::End));

    m_runtime.Execute(&code);

    // Interpret
}