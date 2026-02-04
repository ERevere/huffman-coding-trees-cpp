#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <istream>


namespace hec {
inline constexpr std::array<char,4> kMagic = {'H','E','C','1'};

struct FileHeader {
    std::array<char,4> magic = kMagic;
    std::uint64_t originalSize = 0;
};
bool writeHeader(std::ostream&, const FileHeader&);
bool readHeader(std::istream&, FileHeader&);

}

