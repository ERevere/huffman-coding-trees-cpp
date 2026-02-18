#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "include/huffman/decoder.h"
#include "include/huffman/bit_io.h"
#include "include/huffman/format.h"
#include "include/huffman/frequency_table.h"
#include "include/huffman/huffman_tree.h"

namespace hec {

std::string hecDecoder::decode() {
  if (data_.tree == nullptr) {
    if (data_.originalSize != 0)
      throw std::logic_error("Missing tree");
    else
      return "";
  }

  std::istringstream bitIn(data_.bitstream);
  BitReader br(bitIn);

  std::uint64_t produced = 0;
  std::string out;
  out.reserve(static_cast<size_t>(data_.originalSize));

  hmTreeNode *root = data_.tree.get();
  hmTreeNode *current = root;

  if (root->isLeaf()) {
    while (produced < data_.originalSize) {
      out.push_back(root->ch);
      produced++;
    }
    return out;
  }

  bool bit = false;
  while (produced < data_.originalSize) {
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
  if (!out.is_open())
    throw std::logic_error("Output file not found for writing");
  if (!in.is_open())
    throw std::logic_error("Input file not found for decoding");
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
  return;
}

} // namespace hec
