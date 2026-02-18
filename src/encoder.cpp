#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>

#include "include/huffman/encoder.h"
#include "include/huffman/bit_io.h"
#include "include/huffman/format.h"
#include "include/huffman/frequency_table.h"

namespace hec {

inline static void dfs(const hmTreeNode *node, std::string &path,
                       std::array<std::string, 256> &codes) {
  if (node == nullptr) {
    throw std::logic_error("Invalid node met whilst building tree");
  }

  if (node->isLeaf()) {
    codes[static_cast<unsigned char>(node->ch)] = path;
    return;
  }

  if (node->left) {
    path.push_back('0');
    dfs(node->left.get(), path, codes);
    path.pop_back();
  }

  if (node->right) {
    path.push_back('1');
    dfs(node->right.get(), path, codes);
    path.pop_back();
  }
}

EncodedData hecEncoder::encode(std::string &str) {
  hec::FrequencyTable table;
  const size_t len = str.length();

  for (size_t idx = 0; idx < len; ++idx) {
    unsigned char ch = static_cast<unsigned char>(str[idx]);
    uint8_t byte = static_cast<uint8_t>(ch);
    table.addByte(byte);
  }

  std::vector<std::unique_ptr<hmTreeNode>> minHeap;

  for (size_t bv = 0; bv < 256; ++bv) {
    uint8_t byteVal = static_cast<uint8_t>(bv);
    uint32_t freq = table.countByte(byteVal);

    if (freq != 0) {
      auto node = std::make_unique<hmTreeNode>(
          static_cast<unsigned char>(byteVal), static_cast<unsigned>(freq));
      minHeap.push_back(std::move(node));
    }
  }

  if (minHeap.size() == 0) {
    return EncodedData{0, nullptr, ""};
  } else {
    if (minHeap.size() == 1) {
      return EncodedData{static_cast<uint64_t>(str.size()),
                         std::move(minHeap[0]), ""};
    }
  }

  auto comp = [](const std::unique_ptr<hmTreeNode> &a,
                 const std::unique_ptr<hmTreeNode> &b) {
    return a->freq > b->freq;
  };

  std::make_heap(minHeap.begin(), minHeap.end(), comp);

  while (minHeap.size() > 1) {
    std::pop_heap(minHeap.begin(), minHeap.end(), comp);

    auto left = std::move(minHeap.back());
    minHeap.pop_back();

    std::pop_heap(minHeap.begin(), minHeap.end(), comp);

    auto right = std::move(minHeap.back());
    minHeap.pop_back();

    auto parent =
        std::make_unique<hmTreeNode>(std::move(left), std::move(right));
    minHeap.push_back(std::move(parent));
    std::push_heap(minHeap.begin(), minHeap.end(), comp);
  }

  std::unique_ptr<hmTreeNode> root = std::move(minHeap[0]);
  minHeap.clear();

  std::array<std::string, 256> codes{};
  std::string path;
  dfs(root.get(), path, codes);

  std::ostringstream bitOut;
  BitWriter bw(bitOut);

  for (char ch : str) {
    const auto byteIndex = static_cast<unsigned char>(ch);
    const std::string &code = codes[byteIndex];

    for (char co : code) {
      bw.writeBit(co == '1');
    }
  }

  bw.flush();

  EncodedData data;
  data.originalSize = static_cast<std::uint64_t>(str.size());
  data.tree = std::move(root);
  data.bitstream = bitOut.str();
  return data;
}

bool hecEncoder::encodeFile(const std::string &inPath,
                            const std::string &outPath) {
  std::ifstream in(inPath, std::ios::binary);
  if (!in.is_open())
    return false;

  std::ostringstream inputBuf;
  inputBuf << in.rdbuf();
  std::string input = inputBuf.str();

  EncodedData data = this->encode(input);

  std::ofstream out(outPath, std::ios::binary);
  if (!out.is_open())
    return false;

  FileHeader header;
  header.originalSize = data.originalSize;

  if ((!writeHeader(out, header)) || (!data.tree))
    return false;
  if (data.originalSize == 0)
    return true;

  BitWriter bw(out);
  hmTreeNode::serialiseTree(bw, *data.tree);

  for (unsigned char byte : data.bitstream) {
    bw.writeBits(static_cast<std::uint64_t>(byte), 8);
  }

  bw.flush();
  return !out.fail();
}

} // namespace hec
