#pragma once

#include <memory>
#include <cstdint>
#include <string>

#include "huffman_tree.h"

namespace hec{

struct EncodedData { 
    std::uint64_t originalSize;
    std::unique_ptr<hmTreeNode> tree;
    std::string bitstream;
};

}