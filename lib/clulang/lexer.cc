#include "lexer.hh"

Lexer::Lexer() : Reader(""), FSM(State::Ground) {}

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

void Lexer::forward(State new_state)
{
    rollback();
    transition(new_state);
}

Token Lexer::next()
{
    transition(State::Ground);

    while (peek()) {

        switch (char ch = getch(); state()) {

        case State::Ground: {
            if (std::isspace(ch))
                break;

            switch (ch) {
            case '(':
                return {Token::Kind::LeftParen, {peek(-1), 1}, {.ch = ch}};

            case ')':
                return {Token::Kind::RightParen, {peek(-1), 1}, {.ch = ch}};

            case '#': {
                transition(State::Character);
            } break;

            case '"': {
                transition(State::String);
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
                forward(State::Number);
            } break;
            default: {
                forward(State::Symbol);
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
                if (sym.size() == 1 || Token::is_char(sym))
                    return {Token::Kind::Character,
                            {peek(-(sym.size() + 2)), sym.size() + 2},
                            {.ch = *sym.begin()}};

                return {Token::Kind::Unknown,
                        {peek(-(sym.size() + 2)), sym.size() + 2}};
            } break;

            default: {
                rollback();
                forward(State::Symbol);
            } break;
            }
        } break;

        case State::String: {
            Position start = cursor() - 2;
            while (peek() && *peek() != '"') {
                if (*peek() == '\\')
                    advance();
                advance();
            }
            // the loop only terminates if end of line of dquote found.
            // if end of line, then return Unknown.
            if (!peek())
                return {Token::Kind::Unknown,
                        {peek(-cursor() + start), cursor() - start - 1}};
            // advance the double quote.
            advance();
            Position size = cursor() - start;
            return {Token::Kind::String, {peek(-size), size}};
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
            // rolling back the currently consumed character so that it would be
            // included in the symbol from 'getsym()'
            rollback();

            std::string_view sym = getsym();
            if (Token::is_keyword(sym))
                return {Token::Kind::Keyword, {peek(-sym.size()), sym.size()}};

            return {Token::Kind::Symbol, {peek(-sym.size()), sym.size()}};
        } break;
        }
    }

    if (!peek())
        return {Token::Kind::Eof};

    return {};
}
