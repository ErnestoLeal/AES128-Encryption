#ifndef XORENCRYPT_H
#define XORENCRYPT_H
#include <vector>
#include <cstdint>
std::vector<uint8_t> xorEncrypt(const std::vector<uint8_t> &block, const std::vector<uint8_t> &key);
#endif