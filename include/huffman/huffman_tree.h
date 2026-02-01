#pragma once

#include <string>
#include <variant>
#include <vector>

struct Node {
    Node(char c, unsigned f) : ch(c), freq(f) {}
    Node(Node* l, Node* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
    
    char ch;
    unsigned freq;
    Node* left = nullptr;
    Node* right = nullptr;

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

