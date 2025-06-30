#ifndef DECODE_H
#define DECODE_H

#include "config.h"
#include <array>
#include <string>

class Decode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes;
        std::array<uint8_t, CHAR_COUNT> lengths;
        uint8_t offset;
        double kraftMcMillan();
        void canonicalCodes();

    public:
        Decode(std::string src);
};

#endif
