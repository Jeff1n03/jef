#ifndef ENCODE_H
#define ENCODE_H

#include "HuffmanTree.h"
#include <string>

constexpr uint8_t BYTE_SIZE = 8;

class Encode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes;
        std::array<uint8_t, CHAR_COUNT> lengths;
        uint8_t offset;
        void constructorHelper();

    public:
        Encode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::array<uint64_t, CHAR_COUNT> getCodes();
        std::array<uint8_t, CHAR_COUNT> getLengths();
        uint8_t getOffset();
        void toFile(std::string dest), toFile();
};

#endif
