#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "include/huffman/bit_io.h"
#include "include/huffman/decoder.h"
#include "include/huffman/format.h"
#include "include/huffman/frequency_table.h"
#include "include/huffman/huffman_tree.h"

namespace hec {

std::string hecDecoder::decode() {
  if (mData.tree == nullptr) {
    if (mData.originalSize != 0)
      throw std::logic_error("Missing tree");
    else
      return "";
  }

  std::istringstream bitIn(mData.bitstream);
  BitReader br(bitIn);

  std::uint64_t produced = 0;
  std::string out;
  out.reserve(static_cast<size_t>(mData.originalSize));

  hmTreeNode *root = mData.tree.get();
  hmTreeNode *current = root;

  if (root->isLeaf()) {
    while (produced < mData.originalSize) {
      out.push_back(root->ch);
      produced++;
    }
    return out;
  }

  bool bit = false;
  while (produced < mData.originalSize) {
    if (!br.readBit(bit)) {
      throw std::logic_error("Readbit failure");
    }

    if (bit) {
      if (!current->right) {
        throw std::logic_error(
            "Bits require right move, but no right node exists");
      }
      current = current->right.get();
    } else {
      if (!current->left) {
        throw std::logic_error(
            "Bits require left move, but no left node exists");
      }
      current = current->left.get();
    }

    if (current->isLeaf()) {
      out.push_back(current->ch);
      current = root;
      produced++;
    }
  }

  return out;
}

void hecDecoder::decodeFile(const std::string &inPath,
                            const std::string &outPath) {

  std::uint64_t produced = 0;
  bool bit = false;
  hec::FileHeader hdr;

  std::ifstream in(inPath, std::ios::binary);
  std::ofstream out(outPath, std::ios::binary);

  if (!out.is_open() || !in.is_open())
    throw std::logic_error("In/Output file not found for writing");
  if (!hec::readHeader(in, hdr))
    throw std::logic_error("Header read failed or magic didn't match");
  if (hdr.originalSize == 0) {
    return;
  }

  hec::BitReader br(in);
  auto treeRoot = hmTreeNode::deserialiseTree(br);

  if (!treeRoot)
    throw std::logic_error("Failed to deserialise Huffman tree");

  hmTreeNode *root = treeRoot.get();
  hmTreeNode *current = root;

  if (root->isLeaf()) {
    while (produced < hdr.originalSize) {
      out.put(root->ch);
      if (!out)
        throw std::runtime_error("Output stream failed");
      produced++;
    }
    return;
  }

  while (produced < hdr.originalSize) {
    if (!br.readBit(bit))
      throw std::logic_error("Readbit failure");
    if (bit) {
      if (current->right) {
        current = current->right.get();
      } else {
        throw std::logic_error(
            "Bits require right move, but no right node exists");
      }
    } else {
      if (current->left) {
        current = current->left.get();
      } else {
        throw std::logic_error(
            "Bits require left move, but no left node exists");
      }
    }

    if (current->isLeaf()) {
      out.put(current->ch);
      if (!out)
        throw std::runtime_error("Output stream failed");
      current = root;
      produced++;
    }
  }
  if (out.fail())
    throw std::runtime_error("Output stream failed");
}

} // namespace hec
