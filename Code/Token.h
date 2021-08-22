#pragma once

#include <vector>

enum class TokenType
{
    // Single characters symbols
    BraceLeft,
    BraceRight,
    Comma,
    Dot,
    Equals,
    Exclamation,
    GreaterThan,
    LessThan,
    Minus,
    ParenLeft,
    ParenRight,
    Plus,
    Semicolon,
    Slash,
    Star,

    // Double characters symbols
    ExclamationEquals,
    EqualsEquals,
    GreaterThanEquals,
    LessThanEquals,

    // Keywords
    Else,
    For,
    False,
    If,
    Null,
    Return,
    True,
    Var,
    While,

    // Values
    Identifier,
    Number,
    String,

    // Special symbols
    EndOfFile
};

struct Token
{
    TokenType m_type;
    const char* m_sourceStart;
    const char* m_sourceEnd;
};

using Tokens = std::vector<Token>;

const char* TokenTypeToString(const Token& token);
void PrintToken(const Token& token);
void PrintTokens(const Tokens& tokens);