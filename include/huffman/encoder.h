#pragma once

#include "encoded_data.h"
#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecEncoder {
public:
  explicit hecEncoder(const std::string &str) : mToEncode(str) {}

  EncodedData encode(std::string &str);
  void encodeFile(const std::string &inputPath, const std::string &outputPath);

private:
  std::string mToEncode;
  std::unique_ptr<hmTreeNode> mRoot;
};

} // namespace hec
