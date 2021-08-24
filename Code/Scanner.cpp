#include <unordered_map>
#include "Scanner.h"

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

    // Scan...
    const char* cur = source.c_str();
    const char* last = source.c_str() + source.size() - 1;
    while (cur <= last)
    {
        auto itr = matches.find(*cur);
        if (itr != matches.end())
        {
            for (const TokenMatch& match : itr->second)
            {
                bool isMatch = true;
                int matchLength = (int)match.m_text.size();
                const char* test = cur;
                for (const char c : match.m_text)
                {
                    if (test > last || *test != c)
                    {
                        isMatch = false;
                        break;
                    }
                    test++;
                }

                if (isMatch)
                {
                    tokens.push_back(MakeToken(match.m_tokenType, cur, cur + matchLength));
                    cur += matchLength;
                    break;
                }
            }
        }
        else
        {
            cur++;
        }
    }

    tokens.push_back(MakeToken(TokenType::EndOfFile, last + 1, last + 1));

    return tokens;
}

Token Scanner::MakeToken(const TokenType type, const char* sourceStart, const char* sourceEnd)
{
    Token token;
    token.m_type = type;
    token.m_sourceStart = sourceStart;
    token.m_sourceEnd = sourceEnd;

    return token;
}