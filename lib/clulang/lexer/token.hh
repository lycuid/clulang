#ifndef __TOKEN_HH__
#define __TOKEN_HH__

#include <string>

struct Token {
    enum class Kind {
        Unknown,
        LeftParen,
        RightParen,
        Symbol,
        Keyword,
        Character,
        Number,
        Eof,
    } kind;

    std::string_view span;

    union Literal {
        char ch;
        double num;
    } literal;

    Token(Kind _kind = Token::Kind::Unknown, std::string_view _span = {},
          Literal _lit = {})
        : kind(_kind), span(_span), literal(_lit)
    {
    }

    std::string to_string() const;
};

#endif
