#pragma once

#include "encoded_data.h"
#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecDecoder {
public:
  hecDecoder(EncodedData data) : data_(std::move(data)) {}
  void decodeFile(const std::string &inputPath, const std::string &outputPath);
  std::string decode();

private:
  EncodedData data_;
};

} // namespace hec
