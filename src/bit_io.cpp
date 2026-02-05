#include "include/huffman/bit_io.h"

#include <limits>

namespace hec {

BitWriter::BitWriter(std::ostream &out) : out_(&out) {}

void BitWriter::writeBit(bool bit) {
  byte_ <<= 1;
  byte_ |= static_cast<std::uint8_t>(bit);
  bitCount_++;
  if (bitCount_ == 8) {
    out_->put(static_cast<char>(byte_));
    byte_ = 0;
    bitCount_ = 0;
  }
}

void BitWriter::writeBits(std::uint64_t bts, std::uint8_t bct) {
  if (!bct)
    return;
  for (signed i = bct - 1; i >= 0; --i) {
    bool bit = ((bts >> i) & 1ULL) != 0;
    writeBit(bit);
  }
}

std::uint8_t BitWriter::flush() {
  if (!bitCount_)
    return 0;
  uint8_t padding = 8 - bitCount_;
  byte_ <<= padding;
  out_->put(static_cast<char>(byte_));
  byte_ = 0;
  bitCount_ = 0;
  return padding;
}

void BitWriter::reset() {
  byte_ = 0;
  bitCount_ = 0;
}

std::uint8_t BitWriter::bufferedBitCount() const { return bitCount_; }

BitReader::BitReader(std::istream &in) : in_(&in) {}

bool BitReader::readBit(bool &bit) {
  if (bitPos_ == 8) {
    signed next = in_->get();
    if (next == std::char_traits<char>::eof())
      return false;
    byte_ = static_cast<std::uint8_t>(next);
    bitPos_ = 0;
    haveByte_ = true;
  }
  bit = ((byte_ >> (7 - bitPos_)) & 1u) != 0;
  ++bitPos_;
  return true;
}

bool BitReader::readBits(std::uint64_t &bits, std::uint8_t bitCount) {
  bits = 0;
  for (size_t i = 0; i < bitCount; ++i) {
    bool b = false;
    if (!readBit(b))
      return false;
    bits = (bits << 1) | static_cast<std::uint64_t>(b);
  }
  return true;
}

void BitReader::alignToByte() {
  bitPos_ = 8;
  haveByte_ = false;
}

void BitReader::reset() {
  byte_ = 0;
  bitPos_ = 8;
  haveByte_ = false;
}

std::uint8_t BitReader::remainingBitsInByte() const {
  return (bitPos_ >= 8) ? 0 : static_cast<std::uint8_t>(8 - bitPos_);
}

} // namespace hec