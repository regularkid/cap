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
    code.push_back(static_cast<Byte>(123));
    code.push_back(static_cast<Byte>(Op::Pop));
    code.push_back(static_cast<Byte>(Op::Push));
    code.push_back(static_cast<Byte>(64));
    code.push_back(static_cast<Byte>(Op::Push));
    code.push_back(static_cast<Byte>(32));
    code.push_back(static_cast<Byte>(Op::Pop));
    code.push_back(static_cast<Byte>(Op::Print));
    code.push_back(static_cast<Byte>(Op::Pop));
    code.push_back(static_cast<Byte>(Op::End));
    m_vm.Run(&code);

    // Interpret
}