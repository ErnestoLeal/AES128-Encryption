#include "padBlock.h"
#include "stringToHex.h"
#include "keyExpansion.h"
#include "xorEncrypt.h"
#include "subByte.h"
#include "mixColumns.h"
#include "shiftRows.h"
#include "rotateWord.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

int main() {

    const int blockSize = 16;

    std::string text = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAs";

    std::vector<uint8_t> originalKey = {0x1a, 0x2b, 0x3c, 0x4d, 
                                        0x5e, 0x6f, 0x7a, 0x8b, 
                                        0x9c, 0xad, 0xbe, 0xcf, 
                                        0xda, 0xeb, 0xfc, 0x0d};
                                        

    /*Step 1:
    Creates multiple keys from the original key
    */
std::cout << "PRE Program started expanded" << std::endl;
    std::vector<std::vector<uint8_t>> expandedKey= expandKey(originalKey);
std::cout << "Program started expanded" << std::endl;
    /*Step 2:
    Calculates the number of blocks needed. 
    i is a multiple of 16 (block size)
    */
    std::vector<std::vector<uint8_t>> blockArray;
    for ( std::string::size_type i = 0; i < text.size(); i += blockSize) {
        int length = std::min(static_cast<std::string::size_type>(blockSize), text.size() - i);
        std::vector<uint8_t> block = stringToHex(text, i, length);      
        blockArray.push_back(block);
    }
    // Pad the last block if it is less than 16 bytes

    if (blockArray.back().size() < blockSize) {
        blockArray.back() = padBlock(blockArray.back(), blockSize);
    }

    /*
    Step 3:
    Start encrypting the block using XOR with the key
    */

for (auto& block : blockArray) {
    // Initial AddRoundKey
    block = xorEncrypt(block, expandedKey[0]);

    // Main Rounds (1–9)
    for (int round = 1; round < 10; ++round) {
        subByte(block);                   
        shiftRows(block);                 
        mixColumns(block);                
        block = xorEncrypt(block, expandedKey[round]);  
    }
}
   
    /*
    Step 4:
    Shift rows.
    */
    /*Unnecesary? Bugs?
        for (auto& block : blockArray) {
        shiftRows(block); // Call shiftRows for each individual block
    }*/


    //Prints the blocks
    for (size_t blockIndex = 0; blockIndex < blockArray.size(); blockIndex++) {
            std::cout << "Encrypted Block " << blockIndex + 1 << ": ";
            for (auto byte : blockArray[blockIndex]) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
            }
            std::cout << std::endl;
        }


    std::cout << std::endl;

    return 0;
}