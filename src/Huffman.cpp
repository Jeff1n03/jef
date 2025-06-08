#include "Huffman.h"
#include "HuffmanTree.h"
#include <fstream>

using namespace std;

Huffman::Huffman(string &filename) : filename(filename) {}

string Huffman::getFilename() { return this->filename; }

void Huffman::encode() {
    unordered_map<unsigned char, uint64_t> frequencies = frequencyTable();
    if (frequencies.empty()) {
        return;
    }
    HuffmanTree *huffmanTree = new HuffmanTree{frequencies};
    if (!huffmanTree->getRoot()) {
        return;
    }
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
