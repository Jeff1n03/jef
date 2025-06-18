#ifndef ENCODE_H
#define ENCODE_H

#include "HuffmanTree.h"
#include <string>

class Encode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes = {};
        std::array<uint8_t, CHAR_COUNT> lengths = {};

    public:
        Encode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::array<uint64_t, CHAR_COUNT> getCodes();
        std::array<uint8_t, CHAR_COUNT> getLengths();
        void toFile(std::string dest), toFile();
};

#endif
