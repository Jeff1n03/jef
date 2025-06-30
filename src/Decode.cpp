#include "../include/Decode.h"
#include <fstream>

using namespace std;

Decode::Decode(string src) : src(src) {
    ifstream file(this->src, ios::binary);
    if (!file) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    if (!file.read(reinterpret_cast<char *>(this->lengths.data()),
                   this->lengths.size() * sizeof(uint8_t))) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    if (!file.read(reinterpret_cast<char *>(&this->offset), sizeof(uint8_t))) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    double sum = kraftMcMillan();
    if (sum == 0.0 || sum > 1.0) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    canonicalCodes();
}

double Decode::kraftMcMillan() {
    double sum = 0.0;
    for (uint8_t len : this->lengths) {
        if (len > MAX_BITS) {
            throw length_error(CODE_OVERFLOW);
        }
        if (len > 0) {
            sum += 1.0 / pow(2.0, len);
        }
    }
    return sum;
}

void Decode::canonicalCodes() {
    vector<uint8_t> sorted;
    for (size_t i = 0; i < this->lengths.size(); i++) {
        if (this->lengths[i] > 0) {
            sorted.push_back(i);
        }
    }
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
