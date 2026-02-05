#pragma once

#include "encoded_data.h"
#include "huffman_tree.h"

#include <string>
#include <utility>

namespace hec {

class hecEncoder {
public:
  explicit hecEncoder(const std::string &str) : toEncode(str) {}
  EncodedData encode(std::string &str);

private:
  std::string toEncode;
  std::unique_ptr<hmTreeNode> root;
};

} // namespace hec