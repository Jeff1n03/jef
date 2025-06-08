#include "HuffmanTree.h"
#include <cstdint>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class Huffman {
    private:
        string filename;
        unordered_map<unsigned char, uint64_t> frequencyTable();

    public:
        Huffman(string &filename);
        string getFilename();
        void encode();
};

Huffman::Huffman(string &filename) : filename(filename) {}

string Huffman::getFilename() { return this->filename; }

void Huffman::encode() {
    unordered_map<unsigned char, uint64_t> frequencies = frequencyTable();
    if (frequencies.empty()) {
        return;
    }
    HuffmanTree *huffmanTree = new HuffmanTree{frequencies};
}

unordered_map<unsigned char, uint64_t> Huffman::frequencyTable() {
    unordered_map<unsigned char, uint64_t> frequency;
    ifstream file(this->filename, ios::binary);
    if (file) {
        char byte;
        while (file.get(byte)) {
            frequency[static_cast<unsigned char>(byte)]++;
        }
        file.close();
    }
    return frequency;
}
