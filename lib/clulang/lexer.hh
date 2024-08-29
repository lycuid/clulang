#ifndef __LEXER_HH__
#define __LEXER_HH__

#include <clulang/fsm.hh>
#include <clulang/lexer/token.hh>
#include <clulang/reader.hh>
#include <clulang/trie.hh>
#include <unordered_set>

class AbstractLexer
{
  public:
    enum class State {
        Ground,
        Character,
        String,
        Number,
        Symbol,
    };
};

class Lexer : public Reader,
              private AbstractLexer,
              private FSM<AbstractLexer::State>
{
  private:
    std::string_view getsym();

  public:
    Lexer();
    ~Lexer() = default;

    Token next();
    void forward(State);
};

#endif
