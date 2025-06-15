#include "../include/Encode.h"
#include <fstream>
#include <iostream>

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
    } else {
        cout << "failed" << endl;
    }
    HuffmanTree *huffmanTree = new HuffmanTree{frequencies};
    this->codes = huffmanTree->codeTable(this->lengths);
    if (!this->codes.empty()) {
        canonical();
    }
}

void Encode::canonical() {
    vector<unsigned char> sortedChars;
    for (const auto &pair : this->codes) {
        sortedChars.push_back(pair.first);
    }
    sort(sortedChars.begin(), sortedChars.end(),
         [this](unsigned char a, unsigned char b) {
             if (this->lengths[a] == this->lengths[b]) {
                 return a < b;
             }
             return this->lengths[a] < this->lengths[b];
         });
    uint64_t code = 0;
    this->codes[sortedChars[0]] = code;
    uint8_t prevLen = this->lengths[sortedChars[0]];
    for (int i = 1; i < sortedChars.size(); i++) {
        uint8_t len = this->lengths[sortedChars[i]];
        code = (code + 1) << (len - prevLen);
        this->codes[sortedChars[i]] = code;
        prevLen = len;
    }
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
