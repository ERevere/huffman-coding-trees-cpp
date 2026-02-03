#include "include/huffman/bit_io.h"

#include <limits>

namespace hec {

BitWriter::BitWriter(std::ostream &out) : out_(&out) {}

void BitWriter::writeBit(bool bit) {
    byte_ <<= 1;
    byte_ |= static_cast<std::uint8_t>(bit);
    bitCount_++;
    if(bitCount_ == 8){
        out_->put(static_cast<char>(byte_));
        byte_ = 0;
        bitCount_ = 0;
    }
}

void BitWriter::writeBits(std::uint64_t b, std::uint8_t bc) {

}

std::uint8_t BitWriter::flush() {
    if(bitCount_ == 0) { return 0; }
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

std::uint8_t BitWriter::bufferedBitCount() const {
    return bitCount_;
}

BitReader::BitReader(std::istream &in) : in_(&in) {}

bool BitReader::readBit(bool &/*bit*/) {

    return false;
}

bool BitReader::readBits(std::uint64_t &/*bits*/, std::uint8_t /*bitCount*/) {

    return false;
}

void BitReader::alignToByte() {

}

void BitReader::reset() {
    byte_ = 0;
    bitPos_ = 0;
    haveByte_ = 0;
}

std::uint8_t BitReader::remainingBitsInByte() const {
    return (bitPos_ >= 8) ? 0 : static_cast<std::uint8_t>(8 - bitPos_);
}

}