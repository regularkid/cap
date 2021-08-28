#include <unordered_map>
#include "Scanner.h"
#include "Utils.h"

struct TokenMatch
{
    std::string m_text;
    TokenType m_tokenType;
};

void Scanner::ScanTokens(const std::string& source)
{
    // Scan...
    m_line = 1;
    m_sourceCur = source.c_str();
    m_sourceEnd = source.c_str() + source.size();
    while (m_sourceCur < m_sourceEnd)
    {
        if (ScanWhitespace() ||
            ScanComment() ||
            ScanSymbolKeyword() ||
            ScanNumber() ||
            ScanString() ||
            ScanIdentifier())
        {
            continue;
        }

        // Scan function above may have already triggered an error
        if (!m_error)
        {
            LOG("%d: Unexpected character '%c'", m_line, *m_sourceCur);
            m_error = true;
        }

        break;
    }

    // Always append newline at end of valid token stream
    if (!m_error)
    {
        m_tokens.push_back(MakeToken(TokenType::EndOfFile, m_sourceEnd, m_sourceEnd, m_line));
    }
}

bool Scanner::Error() const
{
    return m_error;
}

bool Scanner::ScanWhitespace()
{
    const char c = *m_sourceCur;

    // Ignore whitespace
    if (c == ' ' || c == '\r' || c == '\t')
    {
        ++m_sourceCur;
        return true;
    }

    // Ignore newline
    if (c == '\n')
    {
        ++m_sourceCur;
        ++m_line;
        return true;
    }

    return false;
}

bool Scanner::ScanComment()
{
    const char* testCur = m_sourceCur;
    if (*testCur == '/')
    {
        ++testCur;
        if (testCur < m_sourceEnd && *testCur == '/')
        {
            while (testCur < m_sourceEnd && *testCur != '\n')
            {
                ++testCur;
            }

            m_sourceCur = testCur;
            return true;
        }
    }

    return false;
}

bool Scanner::ScanSymbolKeyword()
{
    // Build matches table
    static std::unordered_map<char, std::vector<TokenMatch>> matches;
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

    // Attempt to match token from matches table
    auto itr = matches.find(*m_sourceCur);
    if (itr != matches.end())
    {
        for (const TokenMatch& match : itr->second)
        {
            bool isMatch = true;
            int matchLength = (int)match.m_text.size();
            const char* testCur = m_sourceCur;
            for (const char cMatch : match.m_text)
            {
                if (testCur >= m_sourceEnd || *testCur != cMatch)
                {
                    isMatch = false;
                    break;
                }
                ++testCur;
            }

            if (isMatch)
            {
                m_tokens.push_back(MakeToken(match.m_tokenType, m_sourceCur, m_sourceCur + matchLength, m_line));
                m_sourceCur += matchLength;
                return true;
            }
        }
    }

    return false;
}

bool Scanner::ScanNumber()
{
    if (!isdigit(*m_sourceCur))
    {
        return false;
    }

    bool encounteredDecimal = false;
    const char* testCur = m_sourceCur + 1;
    while (testCur < m_sourceEnd)
    {
        const char c = *testCur;
        if (isdigit(c))
        {
            ++testCur;
        }
        else if (c == '.' && !encounteredDecimal)
        {
            encounteredDecimal = true;
            ++testCur;
        }
        else
        {
            break;
        }
    }

    int numberLength = int(testCur - m_sourceCur);
    m_tokens.push_back(MakeToken(TokenType::Number, m_sourceCur, m_sourceCur + numberLength, m_line));
    m_sourceCur += numberLength;
    return true;
}

bool Scanner::ScanString()
{
    if (*m_sourceCur != '"')
    {
        return false;
    }

    const char* testCur = m_sourceCur + 1;
    while (testCur < m_sourceEnd && *testCur != '"')
    {
        if (*testCur == '\n')
        {
            m_line++;
        }

        ++testCur;
    }

    if (*testCur != '"')
    {
        LOG("%d: Expected string terminator", m_line);
        m_error = true;
        return false;
    }

    int strLength = int(testCur - m_sourceCur);
    m_tokens.push_back(MakeToken(TokenType::String, m_sourceCur + 1, m_sourceCur + strLength, m_line));
    m_sourceCur = ++testCur;
    return true;
}

bool Scanner::ScanIdentifier()
{
    if (!isalpha(*m_sourceCur))
    {
        return false;
    }

    const char* testCur = m_sourceCur + 1;
    while (testCur < m_sourceEnd && isalnum(*testCur))
    {
        ++testCur;
    }

    int identifierLength = int(testCur - m_sourceCur);
    m_tokens.push_back(MakeToken(TokenType::Identifier, m_sourceCur, m_sourceCur + identifierLength, m_line));
    m_sourceCur += identifierLength;
    return true;
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