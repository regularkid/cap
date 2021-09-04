#include "Token.h"
#include "Utils.h"

const char* TokenTypeToString(const TokenType tokenType)
{
    switch (tokenType)
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

    return "UnknownToken";
}

const char* TokenTypeToUserFacingString(const TokenType tokenType)
{
    switch (tokenType)
    {
        case TokenType::None: return "--";
        case TokenType::BraceLeft: return "[";
        case TokenType::BraceRight: return "]";
        case TokenType::Comma: return ",";
        case TokenType::Dot: return ".";
        case TokenType::Equals: return "=";
        case TokenType::Exclamation: return "!";
        case TokenType::GreaterThan: return ">";
        case TokenType::LessThan: return "<";
        case TokenType::Minus: return "-";
        case TokenType::ParenLeft: return "(";
        case TokenType::ParenRight: return ")";
        case TokenType::Plus: return "+";
        case TokenType::Semicolon: return ";";
        case TokenType::Slash: return "/";
        case TokenType::Star: return "*";
        case TokenType::ExclamationEquals: return "!=";
        case TokenType::EqualsEquals: return "==";
        case TokenType::GreaterThanEquals: return ">=";
        case TokenType::LessThanEquals: return "<=";
        case TokenType::Else: return "else";
        case TokenType::For: return "for";
        case TokenType::False: return "false";
        case TokenType::If: return "if";
        case TokenType::Null: return "null";
        case TokenType::Return: return "return";
        case TokenType::True: return "true";
        case TokenType::Var: return "var";
        case TokenType::While: return "while";
        case TokenType::Identifier: return "[Identifier]";
        case TokenType::Number: return "[Number]";
        case TokenType::String: return "[String]";
        case TokenType::EndOfFile: return "end of file";
    }

    return "Unknown Token";
}

void PrintToken(const Token& token)
{
    if (token.m_type != TokenType::EndOfFile)
    {
        LOG("[%s: \"%.*s\"]:%d", TokenTypeToString(token.m_type), int(token.m_sourceEnd - token.m_sourceStart), token.m_sourceStart, token.m_line);
    }
    else
    {
        LOG("[%s]:%d", TokenTypeToString(token.m_type), token.m_line);
    }
}

void PrintTokens(const Tokens& tokens)
{
    for (const Token& token : tokens)
    {
        PrintToken(token);
    }
}