#include "padBlock.h"
#include <vector>
#include <cstdint>

/*
 The block size is 16 bytes. If longer, divide into multiple blocks. If a block is shorter, pad it
*/

std::vector<uint8_t> padBlock(std::vector<uint8_t> block, int blockSize){
    int paddingNeeded = blockSize - block.size();
    for (int i = 0; i < paddingNeeded; i++){
        block.push_back(static_cast<uint8_t>(paddingNeeded));
    }
    return block;
}