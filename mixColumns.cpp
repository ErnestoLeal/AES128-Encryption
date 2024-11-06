#include "mixColumns.h"
#include <vector>
#include <cstdint>

// Function to perform Galois multiplication of a byte by 2
uint8_t galoisMultiplyBy2(uint8_t value) {
    return (value << 1) ^ ((value >> 7) * 0x1b);
}

// Function to perform Galois multiplication of a byte by 3
uint8_t galoisMultiplyBy3(uint8_t value) {
    return galoisMultiplyBy2(value) ^ value;
}

void mixColumns(std::vector<uint8_t> &block) {

    for (size_t i = 0; i < 4; ++i) {

        uint8_t s0 = block[i * 4 + 0];
        uint8_t s1 = block[i * 4 + 1];
        uint8_t s2 = block[i * 4 + 2];
        uint8_t s3 = block[i * 4 + 3];


        block[i * 4 + 0] = galoisMultiplyBy2(s0) ^ galoisMultiplyBy3(s1) ^ s2 ^ s3;
        block[i * 4 + 1] = s0 ^ galoisMultiplyBy2(s1) ^ galoisMultiplyBy3(s2) ^ s3;
        block[i * 4 + 2] = s0 ^ s1 ^ galoisMultiplyBy2(s2) ^ galoisMultiplyBy3(s3);
        block[i * 4 + 3] = galoisMultiplyBy3(s0) ^ s1 ^ s2 ^ galoisMultiplyBy2(s3);
    }
}
