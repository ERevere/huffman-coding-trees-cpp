#include "include/huffman/huffman_tree.h"
#include "include/huffman/bit_io.h"

namespace hec {

void hmTreeNode::serialiseTree(BitWriter &bw, const hmTreeNode &node) {
  if (node.isLeaf()) {
    bw.writeBit(1);
    uint8_t byteValue =
        static_cast<std::uint8_t>(static_cast<unsigned char>(node.ch));
    bw.writeBits(byteValue, 8);
    return;
  }
  bw.writeBit(0);
  serialiseTree(bw, *node.left);
  serialiseTree(bw, *node.right);
}

std::unique_ptr<hmTreeNode> hmTreeNode::deserialiseTree(BitReader &br) {
  bool marker;
  std::uint64_t bits;
  if (!br.readBit(marker))
    return nullptr;

  if (marker) {
    if (!br.readBits(bits, 8))
      return nullptr;
    unsigned char uc = static_cast<unsigned char>(bits);
    char ch = static_cast<char>(uc);
    return std::make_unique<hmTreeNode>(ch, 0);
  } else {
    auto left = deserialiseTree(br);
    auto right = deserialiseTree(br);
    if (left == nullptr || right == nullptr)
      return nullptr;
    return std::make_unique<hmTreeNode>(std::move(left), std::move(right));
  }
}

} // namespace hec
