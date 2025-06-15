#include "../include/Encode.h"
#include <fstream>

using namespace std;

Encode::Encode(string src) : src(src) {
    unordered_map<unsigned char, uint64_t> frequencies;
    ifstream file(this->src, ios::binary);
    if (file) {
        char byte;
        while (file.get(byte)) {
            frequencies[static_cast<unsigned char>(byte)]++;
        }
        file.close();
    }
    HuffmanTree *huffmanTree = new HuffmanTree{frequencies};
    this->codes = huffmanTree->codeTable(this->lengths);
    canonical();
}

void Encode::canonical() {
    // TODO
}

string Encode::getSrc() { return this->src; }

string Encode::getDefaultDest() { return this->src + ".fin"; }

unordered_map<unsigned char, uint64_t> Encode::getCodes() {
    return this->codes;
}

uint8_t *Encode::getLengths() { return this->lengths; }

void Encode::toFile(string dest) {
    // TODO
}

void Encode::toFile() { toFile(getDefaultDest()); }
