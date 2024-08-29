#ifndef __TOKEN_HH__
#define __TOKEN_HH__

#include <array>
#include <string>

class Token
{
  public:
    enum class Kind {
        Unknown,
        LeftParen,
        RightParen,
        Symbol,
        Keyword,
        Character,
        String,
        Number,
        Eof,
    } kind;

    std::string_view span;

    union Literal {
        char ch;
        double num;
    } literal;

  public:
    Token(Kind = Token::Kind::Unknown, std::string_view = {}, Literal = {});

    std::string to_string() const;

    static bool is_char(std::string_view);
    static bool is_keyword(std::string_view);

    static consteval const std::array<const char *, 3> chars();
    static consteval const std::array<const char *, 4> keywords();
};

#endif
