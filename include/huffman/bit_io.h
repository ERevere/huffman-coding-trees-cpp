#pragma once

#include <cstdint>
#include <istream>
#include <ostream>

namespace hec {

class BitWriter {
public:
  explicit BitWriter(std::ostream &out);
  void writeBit(bool bit);
  void writeBits(std::uint64_t bits, std::uint8_t bitCount);
  std::uint8_t flush();
  void reset();
  std::uint8_t bufferedBitCount() const;

private:
  std::ostream *out_ = nullptr;
  std::uint8_t byte_ = 0;
  std::uint8_t bitCount_ = 0;
};

class BitReader {
public:
  explicit BitReader(std::istream &in);
  bool readBit(bool &bit);
  bool readBits(std::uint64_t &bits, std::uint8_t bitCount);
  void alignToByte();
  void reset();
  std::uint8_t remainingBitsInByte() const;

private:
  std::istream *in_ = nullptr;
  std::uint8_t byte_ = 0;
  std::uint8_t bitPos_ = 8;
  bool haveByte_ = false;
};

} // namespace hec
