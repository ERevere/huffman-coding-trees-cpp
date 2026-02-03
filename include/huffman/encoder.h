#pragma once

#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecEncoder {
public:
    explicit hecEncoder(const std::string &str) : toEncode(str) {}
    std::pair<hmTreeNode*, std::string> encode(std::string &str);

private:
    std::string toEncode;
    hmTreeNode* root = nullptr;
};


}