#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

// Converts string to hexadecimal ASCI values as a vector. They are appended in a vector.
//Takes as parameter the current starting point of the 16byte block and the string length.
std::vector<uint8_t> stringToHex(const std::string &input, int start, int length) {
    std::vector<uint8_t> hexOutPut;
    for (int i = start; i < start + length && i < input.size(); i++) {
        hexOutPut.push_back(static_cast<uint8_t>(input[i]));
    }
    return hexOutPut;
}

//The block size is 16 bytes. If longer, divide into multiple blocks. If a block is shorter, pad it
std::vector<uint8_t> padBlock(std::vector<uint8_t> block, int blockSize = 16){
    int paddingNeeded = blockSize - block.size();
    for (int i = 0; i < paddingNeeded; i++){
        block.push_back(static_cast<uint8_t>(paddingNeeded));
    }
    return block;
}

//XOR Block Generator with block and key.
std::vector<uint8_t> xorEncrypt(const std::vector<uint8_t> &block, const std::vector<uint8_t> &key) {
    std::vector<uint8_t> xorBlock;

//XOR byte operation
    for (size_t i = 0; i < block.size(); i++ ) {
        xorBlock.push_back(block[i]^key[i]);
    }

    return xorBlock;
}


int main() {

    const int blockSize = 16;

    std::string text = "Pene Pene Pene Pene Pene Pene Pene Pene";

    std::vector<uint8_t> key = {0x1a, 0x2b, 0x3c, 0x4d, 
                                0x5e, 0x6f, 0x7a, 0x8b, 
                                0x9c, 0xad, 0xbe, 0xcf, 
                                0xda, 0xeb, 0xfc, 0x0d};

    /*Step 1:
    Calculates the number of blocks needed. 
    i is a multiple of 16 (block size)
    */
    std::vector<std::vector<uint8_t>> blockArray;
    for (int i = 0; i < text.size(); i += blockSize) {
        int length = std::min(blockSize, static_cast<int>(text.size()) - i);
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