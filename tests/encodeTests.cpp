#include "../include/Encode.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    Encode encode = Encode{"tests/data/input-1.txt"};
    array<uint64_t, CHAR_COUNT> actualCodes = encode.getCodes();
    array<uint8_t, CHAR_COUNT> actualLengths = encode.getLengths();
    array<uint64_t, CHAR_COUNT> expectedCodes = {};
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    expectedCodes[static_cast<unsigned char>('\n')] = 0b1110;
    expectedLengths[static_cast<unsigned char>('\n')] = 4;
    expectedCodes[static_cast<unsigned char>('a')] = 0b1111;
    expectedLengths[static_cast<unsigned char>('a')] = 4;
    expectedCodes[static_cast<unsigned char>('b')] = 0b110;
    expectedLengths[static_cast<unsigned char>('b')] = 3;
    expectedCodes[static_cast<unsigned char>('c')] = 0b10;
    expectedLengths[static_cast<unsigned char>('c')] = 2;
    expectedCodes[static_cast<unsigned char>('d')] = 0b0;
    expectedLengths[static_cast<unsigned char>('d')] = 1;
    assert(actualCodes == expectedCodes);
    assert(actualLengths == expectedLengths);
    assert(encode.getOffset() == 2);
}

void testTwo() {
    bool failOpenFile = false, failInitTree = false;
    try {
        Encode encode = Encode{"tests/data/input-0.txt"};
    } catch (const std::exception &e) {
        assert(strcmp(e.what(), FAIL_OPEN_FILE) == 0);
        failOpenFile = true;
    }
    try {
        Encode encode = Encode{"tests/data/input-2.txt"};
    } catch (const std::exception &e) {
        assert(strcmp(e.what(), FAIL_INIT_TREE) == 0);
        failInitTree = true;
    }
    assert(failOpenFile);
    assert(failInitTree);
}

int main() {
    cout << "\nencodeTests: Begin..." << endl;
    testOne();
    cout << "encodeTests: Passed Test 1" << endl;
    testTwo();
    cout << "encodeTests: Passed Test 2" << endl;
    cout << "encodeTests: ...Done" << endl;
    return 0;
}
