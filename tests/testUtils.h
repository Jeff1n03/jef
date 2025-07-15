#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../include/config.h"
#include <fstream>

inline bool isEqual(std::string actual, std::string expected) {
    std::ifstream acFile(actual, std::ios::binary),
        exFile(expected, std::ios::binary);
    if (!acFile) {
        throw std::invalid_argument(std::string(FAIL_READ_FILE) + ' ' + actual);
    }
    if (!exFile) {
        throw std::invalid_argument(std::string(FAIL_READ_FILE) + ' ' +
                                    expected);
    }
    uint8_t ac, ex;
    while (acFile.read(reinterpret_cast<char *>(&ac), sizeof(uint8_t)) &&
           exFile.read(reinterpret_cast<char *>(&ex), sizeof(uint8_t))) {
        if (ac != ex) {
            return false;
        }
    }
    return !acFile.read(reinterpret_cast<char *>(&ac), sizeof(uint8_t)) &&
           !exFile.read(reinterpret_cast<char *>(&ex), sizeof(uint8_t));
}

#endif
