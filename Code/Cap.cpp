#include "Cap.h"
#include "Ops.h"
#include "Utils.h"

// ----------------------------------------------------------------------------
void Cap::Run(const std::string& source)
{
    m_compiler.Compile(source);
    if (m_compiler.Error())
    {
        return;
    }

    // DEBUG: Generate bytecode
    Executable& executable = m_compiler.GetExecutable();
    executable.m_code.push_back(static_cast<Byte>(Op::Constant));
    executable.m_code.push_back(static_cast<Byte>(0));

    executable.m_code.push_back(static_cast<Byte>(Op::Constant));
    executable.m_code.push_back(static_cast<Byte>(1));

    executable.m_code.push_back(static_cast<Byte>(Op::Add));

    executable.m_code.push_back(static_cast<Byte>(Op::Print));
    executable.m_code.push_back(static_cast<Byte>(Op::Pop));

    executable.m_code.push_back(static_cast<Byte>(Op::End));

    m_runtime.Execute(&executable);

    // Interpret
}