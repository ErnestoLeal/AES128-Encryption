#include "addRoundKey.h"
#include <vector>
#include <cstdint>

void addRoundKey(std::vector<uint8_t> &block, const std::vector<uint8_t> &key) {
    for (size_t i = 0; i < 16; i++) {
        block[i] ^= key[i];
    }
}