#pragma once

#include "huffman_tree.h"
#include "encoded_data.h"

#include <string>
#include <utility>

namespace hec {

class hecDecoder {
public:
    hecDecoder(EncodedData data) : data_(std::move(data)){}
    std::string decode();

private:
    EncodedData data_;
};

}