#ifndef UTILS_H
#define UTILS_H

#include <fstream>

inline constexpr size_t CHAR_COUNT = 256, BYTE_SIZE = 8, MAX_BITS = 64;

inline constexpr const char *FILE_EXTENSION = ".fin",
                            *CODE_OVERFLOW = "code exceeds 64 bits",
                            *FAIL_READ_FILE = "failed to read file",
                            *FAIL_WRITE_FILE = "failed to write file";

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
