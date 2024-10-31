#include "stringToHex.h"
#include <vector>
#include <cstdint>
#include <string>
/*
 Converts string to hexadecimal ASCI values as a vector. They are appended in a vector.
Takes as parameter the current starting point of the 16byte block and the string length.
*/

std::vector<uint8_t> stringToHex(const std::string &input, int start, int length) {
    std::vector<uint8_t> hexOutPut;
    for (int i = start; i < start + length && i < input.size(); i++) {
        hexOutPut.push_back(static_cast<uint8_t>(input[i]));
    }
    return hexOutPut;
}