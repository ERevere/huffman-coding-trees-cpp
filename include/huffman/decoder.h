#pragma once

#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecDecoder {
public:
    explicit hecDecoder(std::pair<hmTreeNode*, std::string> &tstr) : treeStream(tstr) {}
    std::string decode();

private:
    std::pair<hmTreeNode*, std::string> treeStream;
    hmTreeNode* root = nullptr;
};

}