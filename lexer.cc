#include "lexer.hh"

Reader::Reader(std::string line) : m_line(line), m_cursor(0) {}

void Reader::feed(std::string line)
{
    m_line   = line;
    m_cursor = 0;
}

const char *Reader::peek(Position at = 0) const
{
    return m_cursor < m_line.size() ? &m_line[cursor() + at] : nullptr;
}

Position Reader::advance() { return m_cursor++; }

Lexer::Lexer() : Reader("") {}

Lexer::Lexer(std::string line) : Reader(line) {}

static inline bool is_valid_symbol_char(char ch) { return !std::isspace(ch); }

Token Lexer::run()
{
    while (peek() && std::isspace(*peek()))
        advance();

    while (peek()) {
        switch (const char *ch = peek(); *ch) {

        case '(': {
            advance();
            return {Token::Kind::LeftParen, {ch, 1}, {.ch = *ch}};
        } break;

        case ')': {
            advance();
            return {Token::Kind::RightParen, {ch, 1}, {.ch = *ch}};
        }

        case '1': [[fallthrough]];
        case '2': [[fallthrough]];
        case '3': [[fallthrough]];
        case '4': [[fallthrough]];
        case '5': [[fallthrough]];
        case '6': [[fallthrough]];
        case '7': [[fallthrough]];
        case '8': [[fallthrough]];
        case '9': {
            Position start = cursor();

            while (peek() && std::isdigit(*peek()))
                advance();

            if (peek() && *peek() == '.' && advance())
                while (peek() && std::isdigit(*peek()))
                    advance();

            Position size = cursor() - start;

            std::string_view span = {peek(-size), size};
            return {Token::Kind::Number, span, {.num = std::atof(span.data())}};
        } break;

        default: {
            if (std::isspace(*peek()))
                continue;

            Position start = cursor();
            for (; is_valid_symbol_char(*peek()); peek())
                advance();
            Position size = cursor() - start;
            return {Token::Kind::Symbol, {peek(-size), size}};
        } break;
        }
    }

    if (!peek())
        return {Token::Kind::Eof};

    return {};
}
