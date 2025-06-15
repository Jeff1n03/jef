#ifndef ENCODE_H
#define ENCODE_H

#include "HuffmanTree.h"
#include <string>

class Encode {
    private:
        std::string src;
        std::unordered_map<unsigned char, uint64_t> codes;
        uint8_t lengths[arrSize];
        void canonical();

    public:
        Encode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::unordered_map<unsigned char, uint64_t> getCodes();
        uint8_t *getLengths();
        void toFile(std::string dest), toFile();
};

#endif
