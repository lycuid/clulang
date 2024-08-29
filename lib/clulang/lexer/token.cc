#include "token.hh"
#include <array>
#include <cstring>

Token::Token(Kind _kind, std::string_view _span, Literal lit)
    : kind(_kind), span(_span), literal(lit)
{
}

consteval const std::array<const char *, 3> Token::chars()
{
    return {"newline", "space", "tab"};
}

consteval const std::array<const char *, 4> Token::keywords()
{
    return {"define", "let", "let*", "letrec"};
}

bool Token::is_char(std::string_view str)
{
    for (const char *ch : chars()) {
        if (std::strlen(ch) == str.size() &&
            std::memcmp(ch, str.begin(), str.size()) == 0) {
            return true;
        }
    }
    return false;
}

bool Token::is_keyword(std::string_view str)
{
    for (const char *kw : keywords()) {
        if (std::strlen(kw) == str.size() &&
            std::memcmp(kw, str.begin(), str.size()) == 0) {
            return true;
        }
    }
    return false;
}

std::string Token::to_string() const
{
    char buffer[128];
    switch (kind) {
    case Kind::Unknown: {
        sprintf(buffer, "Token::Unknown('%s')", std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::LeftParen: {
        sprintf(buffer, "Token::LeftParen: '%s'", std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::RightParen: {
        sprintf(buffer, "Token::RightParen: '%s'", std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Symbol: {
        sprintf(buffer, "Token::Symbol: '%s'", std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Keyword: {
        sprintf(buffer, "Token::Keyword(%s): '%s'", std::string(span).c_str(),
                std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Character: {
        sprintf(buffer, "Token::Character(%c): '%s'", literal.ch,
                std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::String: {
        sprintf(buffer, "Token::String(%s): '%s'", std::string(span).c_str(),
                std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Number: {
        sprintf(buffer, "Token::Number(%f): '%s'", literal.num,
                std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Eof: return "Token::Eof";
    }
    return "";
}
