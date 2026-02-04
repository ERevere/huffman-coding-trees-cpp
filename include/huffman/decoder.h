#pragma once

#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecDecoder {
public:
    hecDecoder(std::pair<std::unique_ptr<hmTreeNode>, std::string> tstr) : treeStream(std::move(tstr)) {}
    std::string decode();

private:
    std::pair<std::unique_ptr<hec::hmTreeNode>, std::string> treeStream;
    hmTreeNode* root() const { return treeStream.first.get(); }
};

}