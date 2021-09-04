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

    m_runtime.Execute(&m_compiler.GetExecutable());
}