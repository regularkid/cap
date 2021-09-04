#include "Compiler.h"
#include "Ops.h"
#include "Token.h"
#include "Utils.h"

#define DEBUG_COMPILER

#define COMPILE_ERROR(s, ...) LOG("[Compile Error] "##s, __VA_ARGS__); printf("\n"); m_error = true;
#define ADD_BYTE(b) m_executable.m_code.push_back(static_cast<Byte>(b))

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

    m_curTokenIdx = -1;
    while (true)
    {
        AdvanceToken();
        CompileExpression();
        
        if (m_error || m_curToken.m_type == TokenType::EndOfFile)
        {
            break;
        }
    }

    // Emit end of executable
    ADD_BYTE(Op::Print);    // DEBUG
    ADD_BYTE(Op::End);

#ifdef DEBUG_COMPILER
    LOG("---------- Begin Executable ----------");
    LOG("Constants:");
    int constIdx = 0;
    for (const Value& value : m_executable.m_constants)
    {
        LOG("%d: %s", constIdx++, ValueToString(value).c_str());
    }

    LOG("Code:");
    LOG("%d bytes", static_cast<int>(m_executable.m_code.size()));
    LOG("---------- End Executable ------------");
#endif
}

void Compiler::AdvanceToken()
{
    m_prevToken = m_curToken;
    m_curToken = m_scanner.GetToken(++m_curTokenIdx);
    m_nextToken = m_scanner.GetToken(m_curTokenIdx);
}

void Compiler::ConsumeExpectedToken(const TokenType tokenType)
{
    if (m_curToken.m_type != tokenType)
    {
        COMPILE_ERROR("%d: Expected '%s'", m_curToken.m_line, TokenTypeToUserFacingString(tokenType));
    }

    AdvanceToken();
}

int Compiler::AddConstant(const Token& token)
{
    const int idx = static_cast<int>(m_executable.m_constants.size());
    if (idx >= UINT8_MAX)
    {
        COMPILE_ERROR("Too many constants");
        return -1;
    }

    switch (token.m_type)
    {
        case TokenType::Number:
        {
            const Value value = Value(static_cast<float>(atof(token.m_sourceStart)));
            m_executable.m_constants.push_back(value);
            ADD_BYTE(Op::Constant);
            ADD_BYTE(idx);
        } break;
    }

    return idx;
}

void Compiler::CompilePrecedence(const ExprPrecedence exprPrecedence)
{
    // Prefix expression
    switch (m_curToken.m_type)
    {
        case TokenType::Number: CompileNumber(); break;
        case TokenType::Minus: CompileUnary(); break;
        case TokenType::ParenLeft: CompileGrouping(); break;
    }

    if (m_error)
    {
        return;
    }

    // Infix expression
    bool infixDone = false;
    while (!infixDone)
    {
        switch (m_curToken.m_type)
        {
            case TokenType::Plus: if (exprPrecedence <= ExprPrecedence::Term) { CompileBinary(); } else { infixDone = true; } break;
            case TokenType::Minus: if (exprPrecedence <= ExprPrecedence::Term) { CompileBinary(); } else { infixDone = true; }  break;
            case TokenType::Star: if (exprPrecedence <= ExprPrecedence::Factor) { CompileBinary(); } else { infixDone = true; }  break;
            case TokenType::Slash: if (exprPrecedence <= ExprPrecedence::Factor) { CompileBinary(); } else { infixDone = true; }  break;
            default: infixDone = true; break;
        }

        if (m_error)
        {
            return;
        }
    }
}

void Compiler::CompileExpression()
{
    CompilePrecedence(ExprPrecedence::Assignment);
}

void Compiler::CompileNumber()
{
    AddConstant(m_curToken);
    AdvanceToken();
}

void Compiler::CompileUnary()
{
    const TokenType curTokenType = m_curToken.m_type;

    AdvanceToken();
    CompilePrecedence(ExprPrecedence::Unary);

    switch (curTokenType)
    {
        case TokenType::Minus: ADD_BYTE(Op::Negate);
    }
}

void Compiler::CompileGrouping()
{
    AdvanceToken();
    CompileExpression();

    if (m_error)
    {
        return;
    }

    ConsumeExpectedToken(TokenType::ParenRight);
}

void Compiler::CompileBinary()
{
    const TokenType curTokenType = m_curToken.m_type;

    ExprPrecedence precedence = ExprPrecedence::None;
    Op op = Op::None;
    switch (curTokenType)
    {
        case TokenType::Plus: precedence = ExprPrecedence::Term; op = Op::Add; break;
        case TokenType::Minus: precedence = ExprPrecedence::Term; op = Op::Subtract; break;
        case TokenType::Star: precedence = ExprPrecedence::Factor; op = Op::Multiply; break;
        case TokenType::Slash: precedence = ExprPrecedence::Factor; op = Op::Divide; break;
    }

    AdvanceToken();
    CompilePrecedence(precedence);
    ADD_BYTE(op);
}