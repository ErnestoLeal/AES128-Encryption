#include "shiftRows.h"
#include <iostream>
#include <vector>
#include <cstdint>

void shiftRows(std::vector<uint8_t> &block) {
    uint8_t temp;
    //Second row shift (+4)
    temp = block[1];
    block[1] = block[5];
    block[5] = block[9];
    block[9] = block[13];
    block[13] = temp;

    //Third row shift (+8)
    temp = block[2];
    block[2] = block[10];
    block[10] = temp;
    temp =  block[6];
    block[6] = block[14];
    block[14] = temp;

    //Fourth word shift (+12)
    temp = block[3];
    block[3] = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7] = temp;
}