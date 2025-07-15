#ifndef DECODE_H
#define DECODE_H

#include "config.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <string>

class Decode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes;
        std::array<uint8_t, CHAR_COUNT> lengths;
        uint8_t offset;
        double kraftMcMillan();
        void canonicalCodes();
        bool toFileHelper(std::ifstream &srcFile, std::ofstream &destFile);

    public:
        Decode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::array<uint64_t, CHAR_COUNT> getCodes();
        std::array<uint8_t, CHAR_COUNT> getLengths();
        size_t getOffset();
        void toFile(std::string dest), toFile();
};

#endif
