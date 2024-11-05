#include "keyExpansion.h"
#include "rotateWord.h"
#include "subByte.h"
#include "addConstant.h"
#include <iostream>
#include <vector>
#include <cstdint>

//Constants
const std::vector<uint8_t> rCon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
const size_t wordSize = 4;
const size_t totalWords = 44;
const size_t totalVectors = 11;
int rConIndex = 0;
//Return vector of vectors for better Readibility and Maintability
//Each array of a vector has a vector
std::vector<std::vector<uint8_t>> expandKey(std::vector<uint8_t> &originalKey) {

    std::vector<std::vector<uint8_t>> expandedKey;
    expandedKey.push_back(originalKey);

    while(expandedKey.size() < totalVectors) {
        std::vector<uint8_t> tempKey(16);
        std::vector<uint8_t> tempWord(4);

        //Copy last word in expandedKey to tempWord
        tempWord.assign(expandedKey[expandedKey.size()-1].end() - wordSize, expandedKey[expandedKey.size()-1].end());

        //This loop helps check the tempWord values for debugging purposes.
        /*for (size_t i = 0; i < wordSize; i++) {
            std::cout << "tempWord["<<i<<"] = " <<std::hex<<static_cast<int>(*(tempWord.end() + i - wordSize)) << std::dec << std::endl;
        }*/

        //Transform tempWord
        rotateWord(tempWord);
        subByte(tempWord);
        tempWord[0] ^= rCon[rConIndex++];

        for (size_t i = 0; i < wordSize; i++) { 
            tempKey[i] = tempWord[i]^expandedKey.back()[i];
        }

        for (size_t i = 1; i < 4; i++) {
            for (size_t j = 0; j < wordSize; j++) {
                tempKey[i * wordSize + j] = tempKey[(i - 1) * wordSize + j] ^ expandedKey.back()[i * wordSize + j];
            }
        }
        expandedKey.push_back(tempKey);
        }
        //std::cout<<"Size of expandedKeys: " <<expandedKey.size()<<std::endl;
    return expandedKey;
    }
    


