#include "lexer.hh"

Lexer::Lexer() : Reader(""), FSM(State::Ground)
{
    chars.add("newline");
    chars.add("space");
    chars.add("tab");

    keywords.add("let");
    keywords.add("letrec");
    keywords.add("let*");
    keywords.add("define");
}

bool is_valid_symbol_char(char ch)
{
    switch (ch) {
    case '(':
    case ')':
    case '"': return false;
    }
    return !std::isspace(ch);
}

std::string_view Lexer::getsym()
{
    Position start = cursor();
    while (peek() && is_valid_symbol_char(*peek()))
        advance();
    Position size = cursor() - start;
    return {peek(-size), size};
}

Token Lexer::next()
{
    transition(State::Ground);

    for (char ch; peek();) {

        if (ch = getch(); std::isspace(ch))
            continue;

        switch (state()) {

        case State::Ground: {
            switch (ch) {
            case '(':
                return {Token::Kind::LeftParen, {peek(-1), 1}, {.ch = ch}};

            case ')':
                return {Token::Kind::RightParen, {peek(-1), 1}, {.ch = ch}};

            case '#': {
                transition(State::Character);
            } break;

            case '1': [[fallthrough]];
            case '2': [[fallthrough]];
            case '3': [[fallthrough]];
            case '4': [[fallthrough]];
            case '5': [[fallthrough]];
            case '6': [[fallthrough]];
            case '7': [[fallthrough]];
            case '8': [[fallthrough]];
            case '9': {
                rollback();
                transition(State::Number);
            } break;
            default: {
                rollback();
                transition(State::Symbol);
            } break;
            }
        } break;

        case State::Character: {
            switch (ch) {
            case '\\': {
                if (!peek())
                    return {Token::Kind::Unknown, {peek(-2), 2}};

                // we know that there is atleast 1 char at this point.
                std::string_view sym = getsym();
                if (sym.size() == 1 || chars.contains(sym))
                    return {Token::Kind::Character,
                            {peek(-(sym.size() + 2)), sym.size() + 2},
                            {.ch = *sym.begin()}};

                return {Token::Kind::Unknown,
                        {peek(-(sym.size() + 2)), sym.size() + 2}};
            } break;
            }
        } break;

        case State::Number: {
            Position start = cursor() - 1;
            while (peek() && std::isdigit(*peek()))
                advance();

            if (peek() && *peek() == '.' && advance())
                while (peek() && std::isdigit(*peek()))
                    advance();

            Position size         = cursor() - start;
            std::string_view span = {peek(-size), size};

            return {Token::Kind::Number, span, {.num = std::atof(span.data())}};
        } break;

        case State::Symbol: {
            // rolling back as a character of the symbol is already consumed.
            rollback();

            std::string_view sym = getsym();
            if (keywords.contains(sym))
                return {Token::Kind::Keyword, {peek(-sym.size()), sym.size()}};

            return {Token::Kind::Symbol, {peek(-sym.size()), sym.size()}};
        } break;
        }
    }

    if (!peek())
        return {Token::Kind::Eof};

    return {};
}
