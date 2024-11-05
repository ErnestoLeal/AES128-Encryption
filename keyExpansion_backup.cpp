#include "keyExpansion.h"
#include "rotateWord.h"
#include "subByte.h"
#include "addConstant.h"
#include <iostream>
#include <vector>
#include <cstdint>

//Constants
const std::vector<uint8_t> rCon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
int rConIndex = 0;
//Return vector of vectors for better Readibility and Maintability
//Each array of a vector has a vector
std::vector<std::vector<uint8_t>> expandKey(std::vector<uint8_t> &cipherKey) {
    std::vector<std::vector<uint8_t>> expandedKey;
    expandedKey.push_back(cipherKey);
    uint8_t wordSize = 4;
    uint8_t wordCount = 4;
    uint8_t totalWords = 44;
    std::vector<uint8_t> tempKey(4);
    while(wordCount < totalWords) {
        //Copy the last word to the temporary variable
        // BUGGED LINE IDK WHY tempKey = {expandedKey.back().end() - wordSize, expandedKey.back().end()};
        tempKey.assign(expandedKey.back().end() - wordSize, expandedKey.back().end());

        if (wordCount % 4 == 0) {
            //rotateWord and subByte functions are defined and explained in their own .cpp file
            rotateWord(tempKey);
            subByte(tempKey);
            //Changes the first byte of each key with a different constant from the rCon vector.
            tempKey[0] ^= rCon[rConIndex++];
        }

        for(size_t i = 0; i < wordSize; i++) {


            tempKey[i] ^= expandedKey[expandedKey.size() - 1][12+i];
            //std::cout << expandedKey.size();
        }
        std::cout << "expandKey.size() = "<<expandedKey.size() <<std::endl;
        expandedKey.push_back(tempKey);
        wordCount++;
        }
    
    return expandedKey;
    }
    


