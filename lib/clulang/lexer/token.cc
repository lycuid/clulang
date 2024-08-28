#include "token.hh"

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
    case Kind::Number: {
        sprintf(buffer, "Token::Number(%f): '%s'", literal.num,
                std::string(span).c_str());
        return std::string(buffer);
    }
    case Kind::Eof: return "Token::Eof";
    }
    return "";
}
