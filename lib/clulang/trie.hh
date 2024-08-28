#ifndef __TRIE_HH__
#define __TRIE_HH__

#include <cstring>
#include <string_view>

class Trie
{
    struct Node {
        Node *children[128];
        bool end;

        Node();
        ~Node();
    } m_head;

  public:
    void add(std::string_view);
    bool contains(std::string_view);

  private:
    Node *head() { return &m_head; }
};

#endif
