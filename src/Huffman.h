#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

class Huffman {
    private:
        std::string filename;
        std::unordered_map<unsigned char, uint64_t> frequencyTable();

    public:
        Huffman(std::string &filename);
        std::string getFilename();
        void encode();
};

#endif
