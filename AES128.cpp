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



int main() {

    const int blockSize = 16;

    std::string text = "Pene Pene Pene Pene Pene Pene Pene Pene";

    std::vector<std::vector<uint8_t>> blockArray;

    //Calculates the number of blocks needed. 
    //i is a multiple of 16 (block size)
    for (int i = 0; i < text.size(); i += blockSize) {

        //Calculates the remaining length of the string of the last block
        int length = std::min(blockSize, static_cast<int>(text.size()) - i);

        std::vector<uint8_t> block = stringToHex(text, i, length);
        
        //Appends block to the blockArray
        blockArray.push_back(block);
    }

    if (blockArray.back().size() < blockSize) {
        blockArray.back() = padBlock(blockArray.back(), blockSize);
    }

for (size_t blockIndex = 0; blockIndex < blockArray.size(); blockIndex++) {
        std::cout << "Hexadecimal Block " << blockIndex + 1 << ": ";
        for (auto byte : blockArray[blockIndex]) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;

    return 0;
}