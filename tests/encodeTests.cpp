#include "../include/Encode.h"
#include "../include/config.h"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

void testOne() {
    Encode encode("tests/data/input-1.txt");
    array<uint64_t, CHAR_COUNT> actualCodes = encode.getCodes();
    array<uint8_t, CHAR_COUNT> actualLengths = encode.getLengths();
    array<uint64_t, CHAR_COUNT> expectedCodes = {};
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    expectedCodes[static_cast<uint8_t>('\n')] = 0b1110;
    expectedLengths[static_cast<uint8_t>('\n')] = 4;
    expectedCodes[static_cast<uint8_t>('a')] = 0b1111;
    expectedLengths[static_cast<uint8_t>('a')] = 4;
    expectedCodes[static_cast<uint8_t>('b')] = 0b110;
    expectedLengths[static_cast<uint8_t>('b')] = 3;
    expectedCodes[static_cast<uint8_t>('c')] = 0b10;
    expectedLengths[static_cast<uint8_t>('c')] = 2;
    expectedCodes[static_cast<uint8_t>('d')] = 0b0;
    expectedLengths[static_cast<uint8_t>('d')] = 1;
    assert(actualCodes == expectedCodes);
    assert(actualLengths == expectedLengths);
    assert(encode.getOffset() == 2);
}

void testTwo() {
    bool failReadFile = false, failInitTree = false;
    try {
        Encode encode("tests/data/input-dne.txt");
    } catch (const std::exception &e) {
        if (strcmp(e.what(), FAIL_READ_FILE) == 0) {
            failReadFile = true;
        }
    }
    try {
        Encode encode("tests/data/input-0.txt");
    } catch (const std::exception &e) {
        if (strcmp(e.what(), FAIL_INIT_TREE) == 0) {
            failInitTree = true;
        }
    }
    assert(failReadFile);
    assert(failInitTree);
}

void testThree() {
    Encode encode("tests/data/input-1.txt");
    encode.toFile();
    ifstream actual(encode.getDefaultDest(), ios::binary),
        expected("tests/data/output-1.txt", ios::binary);
    uint8_t ac, ex;
    while (actual.read(reinterpret_cast<char *>(&ac), sizeof(uint8_t)) &&
           expected.read(reinterpret_cast<char *>(&ex), sizeof(uint8_t))) {
        assert(ac == ex);
    }
    assert(!actual.read(reinterpret_cast<char *>(&ac), sizeof(uint8_t)) &&
           !expected.read(reinterpret_cast<char *>(&ex), sizeof(uint8_t)));
    filesystem::remove(encode.getDefaultDest());
}

int main() {
    cout << "\nencodeTests: Begin..." << endl;
    testOne();
    cout << "encodeTests: Passed Test 1" << endl;
    testTwo();
    cout << "encodeTests: Passed Test 2" << endl;
    testThree();
    cout << "encodeTests: Passed Test 3" << endl;
    cout << "encodeTests: ...Done" << endl;
    return 0;
}
