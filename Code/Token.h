#pragma once

#include <vector>

enum class TokenType
{
    None,

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
    TokenType m_type = TokenType::None;
    const char* m_sourceStart = nullptr;
    const char* m_sourceEnd = nullptr;
    int m_line = -1;
};

using Tokens = std::vector<Token>;

const char* TokenTypeToString(const TokenType tokenType);
const char* TokenTypeToUserFacingString(const TokenType tokenType);
void PrintToken(const Token& token);
void PrintTokens(const Tokens& tokens);