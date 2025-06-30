#include "../include/Encode.h"
#include <fstream>

using namespace std;

Encode::Encode(string src) : src(src) {
    ifstream file(this->src, ios::binary);
    if (!file) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    uint8_t ascii;
    array<uint64_t, CHAR_COUNT> frequencies = {};
    while (file.read(reinterpret_cast<char *>(&ascii), sizeof(uint8_t))) {
        frequencies[ascii]++;
    }
    file.close();
    HuffmanTree *huffmanTreeP = new HuffmanTree(frequencies);
    if (!huffmanTreeP->getRoot()) {
        delete huffmanTreeP;
        throw invalid_argument(FAIL_INIT_TREE);
    }
    if (huffmanTreeP->depth() > MAX_BITS) {
        delete huffmanTreeP;
        throw invalid_argument(CODE_OVERFLOW);
    }
    this->codes = huffmanTreeP->codes(this->lengths);
    delete huffmanTreeP;
    constructorHelper(frequencies);
}

void Encode::constructorHelper(array<uint64_t, CHAR_COUNT> &frequencies) {
    uint64_t bit = 0;
    vector<uint8_t> sorted;
    for (size_t i = 0; i < this->lengths.size(); i++) {
        bit = (bit + (this->lengths[i] * frequencies[i])) % BYTE_SIZE;
        if (this->lengths[i] > 0) {
            sorted.push_back(i);
        }
    }
    this->offset = BYTE_SIZE - bit;
    sort(sorted.begin(), sorted.end(), [this](uint8_t a, uint8_t b) {
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

string Encode::getDefaultDest() { return this->src + FILE_EXTENSION; }

array<uint64_t, CHAR_COUNT> Encode::getCodes() { return this->codes; }

array<uint8_t, CHAR_COUNT> Encode::getLengths() { return this->lengths; }

uint8_t Encode::getOffset() { return this->offset; }

void Encode::toFileHelper(ifstream &srcFile, ofstream &destFile) {
    destFile.write(reinterpret_cast<char *>(this->lengths.data()),
                   this->lengths.size() * sizeof(uint8_t));
    destFile.write(reinterpret_cast<char *>(&this->offset), sizeof(uint8_t));
    uint8_t ascii, mask = 0x1, byte = 0x0, acc = this->offset;
    while (srcFile.read(reinterpret_cast<char *>(&ascii), sizeof(uint8_t))) {
        for (int i = this->lengths[ascii] - 1; i >= 0; i--) {
            uint64_t bit = (this->codes[ascii] >> i) & mask;
            if (bit == 1) {
                byte |= mask;
            }
            acc++;
            if (acc == BYTE_SIZE) {
                destFile.write(reinterpret_cast<char *>(&byte),
                               sizeof(uint8_t));
                acc = 0, byte = 0x0;
            }
            byte <<= 1;
        }
    }
}

void Encode::toFile(string dest) {
    ifstream srcFile(this->src, ios::binary);
    if (!srcFile) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    ofstream destFile(dest, ios::binary);
    if (!destFile) {
        throw invalid_argument(FAIL_WRITE_FILE);
    }
    toFileHelper(srcFile, destFile);
    srcFile.close();
    destFile.close();
}

void Encode::toFile() { toFile(getDefaultDest()); }
