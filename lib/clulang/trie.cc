#include "trie.hh"

Trie::Node::Node() : end(false) { std::memset(children, 0, sizeof(children)); }

Trie::Node::~Node()
{
    for (auto child : children)
        if (child)
            delete child;
}

void Trie::add(std::string_view str)
{
    Node *node = head();
    for (size_t i = 0; i < str.size(); ++i) {
        size_t ch = static_cast<size_t>(str[i]);
        if (!node->children[ch])
            node->children[ch] = new Node();
        node = node->children[ch];
    }
    node->end = true;
}

bool Trie::contains(std::string_view str)
{
    Node *node = head();
    for (size_t i = 0; i < str.size(); ++i) {
        size_t ch = static_cast<size_t>(str[i]);
        if (!node->children[ch])
            return false;
        node = node->children[ch];
    }
    return node->end;
}
