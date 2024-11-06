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

    //Text to be encrypted
    std::string text = "Akram es puto";

    //Custom original key
    std::vector<uint8_t> originalKey = {0x00, 0x11, 0x22, 0x33, 
                                        0x44, 0x55, 0x66, 0x77, 
                                        0x88, 0x99, 0xaa, 0xbb, 
                                        0xcc, 0xdd, 0xee, 0xff};
                                        

    /*Step 1:
    Key Expansion
    */
    std::vector<std::vector<uint8_t>> expandedKey= expandKey(originalKey);

    /*Step 2:
    Block sectioning and padding
    */
    std::vector<std::vector<uint8_t>> blockArray;
    for ( std::string::size_type i = 0; i < text.size(); i += blockSize) {
        int length = std::min(static_cast<std::string::size_type>(blockSize), text.size() - i);
        std::vector<uint8_t> block = stringToHex(text, i, length);      
        blockArray.push_back(block);
    }

    // Padding if needed
    if (blockArray.back().size() < blockSize) {
        blockArray.back() = padBlock(blockArray.back(), blockSize);
    }

    /*
    Step 3:
    Encryption
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

        // Final Round (round 10) 
        subByte(block); 
        shiftRows(block); 
        block = xorEncrypt(block, expandedKey[10]);
    }

    //Print the encrypted blocks
    std::cout << std::endl;
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