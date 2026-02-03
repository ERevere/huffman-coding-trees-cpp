#pragma once

#include <array>
#include <cstdint>
#include <numeric>

namespace hec {
struct FrequencyTable {
    std::array<std::uint32_t, 256> table{};

    void addByte(std::uint8_t byte) {
        this->table[static_cast<unsigned char>(byte)]++;
    }

    std::uint32_t countByte(std::uint8_t byte) const {
        return this->table[static_cast<unsigned char>(byte)];
    }

    bool empty() const{
        return std::accumulate(table.begin(), table.end(), 0) == 0;
    }

    size_t total() const {
        return std::accumulate(table.begin(), table.end(), std::uint64_t{0});
    }
};
}
