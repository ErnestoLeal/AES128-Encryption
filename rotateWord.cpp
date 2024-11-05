#include "rotateWord.h"
#include <vector>
#include <cstdint>

void rotateWord(std::vector<uint8_t> &word){
    uint8_t temp;
    temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}