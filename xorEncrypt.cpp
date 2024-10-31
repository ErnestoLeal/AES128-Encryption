#include "xorEncrypt.h"
#include <vector>
#include <cstdint>
//XOR Block Generator with block and key.
std::vector<uint8_t> xorEncrypt(const std::vector<uint8_t> &block, const std::vector<uint8_t> &key) {
    std::vector<uint8_t> xorBlock;

//XOR byte operation
    for (size_t i = 0; i < block.size(); i++ ) {
        xorBlock.push_back(block[i]^key[i]);
    }

    return xorBlock;
}