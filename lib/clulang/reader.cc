#include "reader.hh"

template <class T> constexpr static inline bool between(T i, T a, T b)
{
    return a < i && i < b;
}

Reader::Reader(std::string line) : m_line(line), m_cursor(0) {}

void Reader::feed(std::string line)
{
    m_line   = line;
    m_cursor = 0;
}

const char *Reader::peek(Position at) const
{
    return between<int>(m_cursor + at, -1, m_line.size())
               ? &m_line[cursor() + at]
               : nullptr;
}

char Reader::getch() { return m_line[m_cursor++]; }

Position Reader::advance(Position step) { return m_cursor += step; }
Position Reader::rollback(Position step) { return advance(-step); }
