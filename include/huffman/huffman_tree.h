#pragma once

#include <memory>

namespace hec {

class BitWriter;
class BitReader;

struct hmTreeNode {
  hmTreeNode(char c, unsigned f) : ch(c), freq(f) {}

  hmTreeNode(std::unique_ptr<hmTreeNode> l, std::unique_ptr<hmTreeNode> r)
      : ch(0), freq(l->freq + r->freq), left(std::move(l)),
        right(std::move(r)) {}

  char ch{};
  unsigned freq{};
  std::unique_ptr<hmTreeNode> left{};
  std::unique_ptr<hmTreeNode> right{};

  bool isLeaf() const { return left == nullptr && right == nullptr; }

  static void serialiseTree(BitWriter &bw, const hmTreeNode &node);
  static std::unique_ptr<hmTreeNode> deserialiseTree(BitReader &br);
};
} // namespace hec
