#include "include/huffman/format.h"

namespace hec {

bool writeHeader(std::ostream &out, const FileHeader &header) {
  for (char c : header.magic) {
    out.put(c);
  }
  for (size_t i = 0; i < sizeof(header.originalSize); ++i) {
    auto byte_i =
        (header.originalSize >> (sizeof(header.originalSize) * i)) & 0xFF;
    out.put(static_cast<char>(byte_i));
    if (!out) {
      return false;
    }
  }
  return !out.fail();
}

bool readHeader(std::istream &in, FileHeader &header) {
  std::array<char, kMagic.size()> magicBuf;
  const size_t byteSized = sizeof(header.originalSize);

  if (in.read(magicBuf.data(), magicBuf.size())) {
    for (size_t i = 0; i < header.magic.size(); ++i) {
      header.magic[i] = magicBuf[i];
    }

    if (header.magic == kMagic) {
      char buf[byteSized];
      std::uint64_t value = 0;

      if (in.read(buf, byteSized)) {

        for (size_t i = 0; i < byteSized; ++i) {
          uint8_t byte = (unsigned char)buf[i];
          value |= (uint64_t(byte) << (8 * i));
        }

        header.originalSize = value;
        return true;
      }
    }
  }
  return false;
}
} // namespace hec