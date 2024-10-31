#include "padBlock.h"
#include "stringToHex.h"
#include "xorEncrypt.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

int main() {

    const int blockSize = 16;

    std::string text = "Hola, muy buenas a todos, guapisimos, aqui vegeta777";

    std::vector<uint8_t> key = {0x1a, 0x2b, 0x3c, 0x4d, 
                                0x5e, 0x6f, 0x7a, 0x8b, 
                                0x9c, 0xad, 0xbe, 0xcf, 
                                0xda, 0xeb, 0xfc, 0x0d};

    /*Step 1:
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

    /*Step 2:
    Start encrypting the block using XOR with the key
    */

   std::vector<std::vector<uint8_t>> xorBlocks;
   for (const auto& block : blockArray) {
    xorBlocks.push_back(xorEncrypt(block, key));
   }

//Prints the blocks
for (size_t blockIndex = 0; blockIndex < blockArray.size(); blockIndex++) {
        std::cout << "Encrypted Block " << blockIndex + 1 << ": ";
        for (auto byte : xorBlocks[blockIndex]) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;

    return 0;
}