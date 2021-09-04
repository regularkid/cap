#pragma once

#include <string>
#include "Executable.h"
#include "Scanner.h"

enum class ExprPrecedence
{
    None,
    Assignment,
    Or,
    And,
    Equality,
    Comparison,
    Term,
    Factor,
    Unary,
    Call,
    Primary
};

class Compiler
{
public:
    void Compile(const std::string& source);
    bool Error() const { return m_error; }

    Executable& GetExecutable() { return m_executable; }    // TODO: Make constant

private:
    void AdvanceToken();
    void ConsumeExpectedToken(const TokenType tokenType);
    int AddConstant(const Token& token);

    void CompilePrecedence(const ExprPrecedence exprPrecedence);
    void CompileExpression();
    void CompileNumber();
    void CompileUnary();
    void CompileGrouping();
    void CompileBinary();

    bool m_error = false;
    Scanner m_scanner;
    Executable m_executable;

    int m_curTokenIdx = -1;
    Token m_curToken;
    Token m_prevToken;
    Token m_nextToken;
};