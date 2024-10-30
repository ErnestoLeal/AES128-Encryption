#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>



std::vector<uint8_t> stringToHex(const std::string &input) {
    std::vector<uint8_t> hexOutPut;
    for (char c : input) {
        hexOutPut.push_back(static_cast<uint8_t>(c));
    }
    return hexOutPut;
}

std::vector<uint8_t> padBlock(std::vector<uint8_t> block, int blockSize = 16){
    int paddingNeeded = blockSize - block.size();
    for (int i = 0; i < paddingNeeded; i++){
        block.push_back(static_cast<uint8_t>(paddingNeeded));
    }
    return block;
}

int main() {

    std::string text = "Te amo";

    std::vector<uint8_t> hexBlock = stringToHex(text);

    hexBlock = padBlock(hexBlock);

    std::cout << "Hexadecimal Block:";

    for (auto byte : hexBlock) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " "; 

    }

    std::cout << std::endl;

    return 0;
}