#include "Compiler.h"
#include "Token.h"
#include "Utils.h"

#define DEBUG_COMPILER

void Compiler::Compile(const std::string& source)
{
    m_scanner.ScanTokens(source);
    if (m_scanner.Error())
    {
        m_error = true;
        return;
    }

#ifdef DEBUG_COMPILER
    LOG("---------- Begin Tokens ----------");
    PrintTokens(m_scanner.GetTokens());
    LOG("---------- End Tokens ------------");
#endif

    for (const Token& token : m_scanner.GetTokens())
    {
        // TEMP/DEBUG
        if (token.m_type == TokenType::Number)
        {
            AddConstant(token);
        }
    }

#ifdef DEBUG_COMPILER
    LOG("---------- Begin Executable ----------");
    LOG("Constants:");
    int constIdx = 0;
    for (const Value& value : m_executable.m_constants)
    {
        LOG("%d: %s", constIdx++, ValueToString(value).c_str());
    }

    LOG("Ops:");
    // TODO LOG("%s", ExecutableOpToString(m_ip).c_str());
    LOG("---------- End Executable ------------");
#endif
}

int Compiler::AddConstant(const Token& token)
{
    const int idx = static_cast<int>(m_executable.m_constants.size());

    switch (token.m_type)
    {
        case TokenType::Number:
        {
            const Value value = Value(static_cast<float>(atof(token.m_sourceStart)));
            m_executable.m_constants.push_back(value);
        } break;
    }

    return idx;
}