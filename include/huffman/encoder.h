#pragma once

#include <string>
#include <variant>
#include <vector>

#include "huffman_tree.h"

namespace hec {

    class hecEncoder {
    public:
        explicit hecEncoder(const std::string& str) : toEncode(str) {}

    private:
        std::string toEncode;
        Node* root = nullptr;
    };


}