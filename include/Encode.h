#ifndef ENCODE_H
#define ENCODE_H

#include "HuffmanTree.h"
#include <string>

inline constexpr size_t BYTE_SIZE = 8;
inline constexpr const char *FAIL_OPEN_FILE = "failed to open file",
                            *FAIL_INIT_TREE = "failed to initialize "
                                              "huffman tree";

class Encode {
    private:
        std::string src;
        std::array<uint64_t, CHAR_COUNT> codes;
        std::array<uint8_t, CHAR_COUNT> lengths;
        uint8_t offset;
        void constructorHelper(std::array<uint64_t, CHAR_COUNT> &frequencies);
        void toFileHelper(std::ifstream &srcFile, std::ofstream &destFile);

    public:
        Encode(std::string src);
        std::string getSrc(), getDefaultDest();
        std::array<uint64_t, CHAR_COUNT> getCodes();
        std::array<uint8_t, CHAR_COUNT> getLengths();
        uint8_t getOffset();
        void toFile(std::string dest), toFile();
};

#endif
