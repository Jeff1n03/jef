#include "../include/Encode.h"
#include <fstream>

using namespace std;

Encode::Encode(string src) : src(src) {
    ifstream file(this->src, ios::binary);
    if (!file) {
        throw invalid_argument("failed to open file");
    }
    unsigned char ascii;
    array<uint64_t, CHAR_COUNT> frequencies = {};
    while (file.read(reinterpret_cast<char *>(&ascii), sizeof(unsigned char))) {
        frequencies[ascii]++;
    }
    file.close();
    unique_ptr<HuffmanTree> huffmanTree = make_unique<HuffmanTree>(frequencies);
    if (!huffmanTree->getRoot()) {
        throw invalid_argument("failed to initialize huffman tree");
    }
    this->codes = huffmanTree->codes(this->lengths);
    vector<unsigned char> sorted;
    for (size_t i = 0; i < CHAR_COUNT; i++) {
        if (this->lengths[i] > 0) {
            sorted.push_back(static_cast<unsigned char>(i));
        }
    }
    sort(sorted.begin(), sorted.end(),
         [this](unsigned char a, unsigned char b) {
             if (this->lengths[a] == this->lengths[b]) {
                 return a < b;
             }
             return this->lengths[a] < this->lengths[b];
         });
    uint64_t code = 0;
    this->codes[sorted[0]] = code;
    uint8_t prevLen = this->lengths[sorted[0]];
    for (size_t i = 1; i < sorted.size(); i++) {
        uint8_t len = this->lengths[sorted[i]];
        code = (code + 1) << (len - prevLen);
        this->codes[sorted[i]] = code;
        prevLen = len;
    }
}

string Encode::getSrc() { return this->src; }

string Encode::getDefaultDest() { return this->src + ".fin"; }

array<uint64_t, CHAR_COUNT> Encode::getCodes() { return this->codes; }

array<uint8_t, CHAR_COUNT> Encode::getLengths() { return this->lengths; }

void Encode::toFile(string dest) {
    // TODO
}

void Encode::toFile() { toFile(getDefaultDest()); }
