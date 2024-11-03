#ifndef ADDROUNDKEY_H
#define ADDROUNDKEY_H
#include <vector>
#include <cstdint>
void addRoundKey(std::vector<uint8_t> &block, const std::vector<uint8_t> &key);
#endif