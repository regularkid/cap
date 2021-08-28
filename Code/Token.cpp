#include "Token.h"
#include "Utils.h"

const char* TokenTypeToString(const Token& token)
{
    switch (token.m_type)
    {
        case TokenType::None: return "None";
        case TokenType::BraceLeft: return "BraceLeft";
        case TokenType::BraceRight: return "BraceRight";
        case TokenType::Comma: return "Comma";
        case TokenType::Dot: return "Dot";
        case TokenType::Equals: return "Equals";
        case TokenType::Exclamation: return "Exclamation";
        case TokenType::GreaterThan: return "GreaterThan";
        case TokenType::LessThan: return "LessThan";
        case TokenType::Minus: return "Minus";
        case TokenType::ParenLeft: return "ParenLeft";
        case TokenType::ParenRight: return "ParenRight";
        case TokenType::Plus: return "Plus";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::Slash: return "Slash";
        case TokenType::Star: return "Star";
        case TokenType::ExclamationEquals: return "ExclamationEquals";
        case TokenType::EqualsEquals: return "EqualsEquals";
        case TokenType::GreaterThanEquals: return "GreaterThanEquals";
        case TokenType::LessThanEquals: return "LessThanEquals";
        case TokenType::Else: return "Else";
        case TokenType::For: return "For";
        case TokenType::False: return "False";
        case TokenType::If: return "If";
        case TokenType::Null: return "Null";
        case TokenType::Return: return "Return";
        case TokenType::True: return "True";
        case TokenType::Var: return "Var";
        case TokenType::While: return "While";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Number: return "Number";
        case TokenType::String: return "String";
        case TokenType::EndOfFile: return "EndOfFile";
    }

    return "UnexpectedToken";
}

void PrintToken(const Token& token)
{
    if (token.m_type != TokenType::EndOfFile)
    {
        LOG("[%s: \"%.*s\" ]:%d", TokenTypeToString(token), int(token.m_sourceEnd - token.m_sourceStart), token.m_sourceStart, token.m_line);
    }
    else
    {
        LOG("[%s]:%d", TokenTypeToString(token), token.m_line);
    }
}

void PrintTokens(const Tokens& tokens)
{
    for (const Token& token : tokens)
    {
        PrintToken(token);
    }
}