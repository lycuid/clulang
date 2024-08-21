#ifndef __LEXER_HH__
#define __LEXER_HH__

#include <cstdlib>
#include <format>
#include <string>

typedef size_t Position;

class Reader
{
    std::string m_line;
    Position m_cursor;

  public:
    Reader(std::string);
    ~Reader() = default;

  protected:
    Position cursor() const { return m_cursor; }

    void feed(std::string);
    const char *peek(Position) const;
    Position advance();
};

struct Token {
    enum class Kind {
        Unknown,
        LeftParen,
        RightParen,
        Symbol,
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

    __attribute__((always_inline)) inline std::string to_string() const
    {
        switch (kind) {
        case Kind::Unknown: return "Token::Kind::Unknown";
        case Kind::LeftParen: return "Token::Kind::LeftParen";
        case Kind::RightParen: return "Token::Kind::RightParen";
        case Kind::Symbol:
            return std::format("Token::Kind::Symbol('{}')", std::string{span});
        case Kind::Number:
            return std::format("Token::Kind::Number({})", literal.num);
        case Kind::Eof: return "Token::Kind::Eof";
        default: return "";
        }
    }
};

class Lexer : private Reader
{
  public:
    Lexer();
    Lexer(std::string);

    void feed(std::string line) { Reader::feed(line); }

    Token run();
};

#endif
