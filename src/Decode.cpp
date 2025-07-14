#include "../include/Decode.h"
#include "../include/Encode.h"

using namespace std;

Decode::Decode(string src) : src(src), codes({}) {
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
    if (sum > 1.0) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    if (sum > 0.0) {
        canonicalCodes();
    }
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

string Decode::getSrc() { return this->src; }

string Decode::getDefaultDest() {
    return this->src.substr(0, this->src.size() - strlen(FILE_EXTENSION));
}

array<uint64_t, CHAR_COUNT> Decode::getCodes() { return this->codes; }

array<uint8_t, CHAR_COUNT> Decode::getLengths() { return this->lengths; }

size_t Decode::getOffset() { return this->offset; }

bool Decode::toFileHelper(ifstream &srcFile, ofstream &destFile) {
    uint8_t byte, mask = 0x1, len = 0, pad = this->offset;
    uint64_t code = 0;
    while (srcFile.read(reinterpret_cast<char *>(&byte), sizeof(uint8_t))) {
        for (int i = BYTE_SIZE - 1 - pad; i >= 0; i--) {
            code <<= 1;
            if (((byte >> i) & mask) == 1) {
                code |= mask;
            }
            len++;
            if (len > MAX_BITS) {
                return false;
            }
            for (size_t j = 0; j < CHAR_COUNT; j++) {
                if (this->codes[j] == code && this->lengths[j] == len) {
                    uint8_t ascii = j;
                    destFile.write(reinterpret_cast<char *>(&ascii),
                                   sizeof(uint8_t));
                    code = 0, len = 0;
                    break;
                }
            }
        }
        pad = 0;
    }
    return code == 0 && len == 0;
}

void Decode::toFile(string dest) {
    ifstream srcFile(this->src, ios::binary);
    if (!srcFile) {
        throw invalid_argument(FAIL_READ_FILE);
    }
    srcFile.seekg(this->lengths.size() * sizeof(uint8_t) + sizeof(uint8_t));
    ofstream destFile(dest, ios::binary);
    if (!destFile) {
        throw invalid_argument(FAIL_WRITE_FILE);
    }
    bool valid = toFileHelper(srcFile, destFile);
    srcFile.close();
    destFile.close();
    if (!valid) {
        remove(dest.c_str());
        throw invalid_argument(FAIL_READ_FILE);
    }
    Encode expected(dest);
    if (expected.getCodes() != this->codes ||
        expected.getLengths() != this->lengths ||
        expected.getOffset() != this->offset) {
        remove(dest.c_str());
        throw invalid_argument(FAIL_READ_FILE);
    }
}

void Decode::toFile() { toFile(getDefaultDest()); }
