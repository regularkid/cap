#include <unordered_map>
#include "Scanner.h"
#include "Utils.h"

struct TokenMatch
{
    std::string m_text;
    TokenType m_tokenType;
};

Tokens Scanner::ScanTokens(const std::string& source)
{
    Tokens tokens;

    // Build matches table
    std::unordered_map<char, std::vector<TokenMatch>> matches;
    matches['{'] = { {"{", TokenType::BraceLeft} };
    matches['}'] = { {"}", TokenType::BraceRight} };
    matches[','] = { {",", TokenType::Comma} };
    matches['.'] = { {".", TokenType::Dot} };
    matches['='] = { {"==", TokenType::EqualsEquals}, {"=", TokenType::Equals} };
    matches['!'] = { {"!=", TokenType::ExclamationEquals}, {"!", TokenType::Exclamation} };
    matches['>'] = { {">=", TokenType::GreaterThanEquals}, {">", TokenType::GreaterThan} };
    matches['<'] = { {"<=", TokenType::LessThanEquals}, {"<", TokenType::LessThan} };
    matches['-'] = { {"-", TokenType::Minus} };
    matches['('] = { {"(", TokenType::ParenLeft} };
    matches[')'] = { {")", TokenType::ParenRight} };
    matches['+'] = { {"+", TokenType::Plus} };
    matches[';'] = { {";", TokenType::Semicolon} };
    matches['/'] = { {"/", TokenType::Slash} };
    matches['*'] = { {"*", TokenType::Star} };
    matches['e'] = { {"else", TokenType::Else} };
    matches['f'] = { {"false", TokenType::False}, {"for", TokenType::For} };
    matches['i'] = { {"if", TokenType::If} };
    matches['n'] = { {"null", TokenType::Null} };
    matches['r'] = { {"return", TokenType::Return} };
    matches['t'] = { {"true", TokenType::True} };
    matches['v'] = { {"var", TokenType::Var} };
    matches['w'] = { {"while", TokenType::While} };

    // Scan...
    int line = 1;
    const char* sourceCur = source.c_str();
    const char* sourceEnd = source.c_str() + source.size();
    while (sourceCur < sourceEnd)
    {
        // Ignore whitespace
        const char c = *sourceCur;
        if (c == ' ' || c == '\r' || c == '\t')
        {
            ++sourceCur;
            continue;
        }

        // Ignore newline
        if (c == '\n')
        {
            ++sourceCur;
            ++line;
            continue;
        }

        // Match token?
        bool foundMatch = false;
        auto itr = matches.find(c);
        if (itr != matches.end())
        {
            for (const TokenMatch& match : itr->second)
            {
                bool isMatch = true;
                int matchLength = (int)match.m_text.size();
                const char* testCur = sourceCur;
                for (const char cMatch : match.m_text)
                {
                    if (testCur >= sourceEnd || *testCur != cMatch)
                    {
                        isMatch = false;
                        break;
                    }
                    ++testCur;
                }

                if (isMatch)
                {
                    tokens.push_back(MakeToken(match.m_tokenType, sourceCur, sourceCur + matchLength, line));
                    sourceCur += matchLength;
                    foundMatch = true;
                    break;
                }
            }
        }

        // Unable to find valid token
        if (!foundMatch)
        {
            LOG("Unexpected character '%c' at line %d", *sourceCur, line);
            m_error = true;
            break;
        }
    }

    // Newline at end of file 
    if (!m_error)
    {
        tokens.push_back(MakeToken(TokenType::EndOfFile, sourceEnd, sourceEnd, line));
    }

    return tokens;
}

bool Scanner::Error() const
{
    return m_error;
}

Token Scanner::MakeToken(const TokenType type, const char* sourceStart, const char* sourceEnd, const int line)
{
    Token token;
    token.m_type = type;
    token.m_sourceStart = sourceStart;
    token.m_sourceEnd = sourceEnd;
    token.m_line = line;

    return token;
}