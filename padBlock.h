#ifndef PADBLOCK_H
#define PADBLOCK_H
#include <vector>
#include <cstdint>
std::vector<uint8_t> padBlock(std::vector<uint8_t> block, int blockSize = 16);
#endif