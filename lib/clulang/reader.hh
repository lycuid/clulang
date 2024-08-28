#ifndef __READER_HH__
#define __READER_HH__

#include <string>

typedef size_t Position;

class Reader
{
    std::string m_line;
    Position m_cursor;

  public:
    Reader(std::string);
    ~Reader() = default;

    void feed(std::string);

  protected:
    Position cursor() const { return m_cursor; }

    const char *peek(Position = 0) const;
    char getch();
    Position advance(Position = 1);
    Position rollback(Position = 1);
};

#endif
