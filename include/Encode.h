#ifndef ENCODE_H
#define ENCODE_H

#include "utils.h"
#include <vector>

class Encode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes;
        std::array<uint8_t, CHAR_COUNT> lengths;
        uint8_t offset;
        void canonicalCodes(std::array<uint64_t, CHAR_COUNT> &frequencies),
            canonicalCodesHelper(std::vector<uint8_t> &sorted),
            toFileHelper(std::ifstream &srcFile, std::ofstream &destFile);

    public:
        Encode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::array<uint64_t, CHAR_COUNT> getCodes();
        std::array<uint8_t, CHAR_COUNT> getLengths();
        size_t getOffset();
        void toFile(std::string dest), toFile();
};

#endif
