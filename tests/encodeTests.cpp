#include "../include/Encode.h"
#include "testUtils.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    string srcFile = "tests/data/input-0.txt";
    Encode encode(srcFile);
    assert(encode.getSrc() == srcFile);
    assert(encode.getDefaultDest() == srcFile + FILE_EXTENSION);
    assert((encode.getCodes() == array<uint64_t, CHAR_COUNT>()));
    assert((encode.getLengths() == array<uint8_t, CHAR_COUNT>()));
    assert(encode.getOffset() == 0);
    encode.toFile();
    assert(isEqual(encode.getDefaultDest(), "tests/data/output-0.txt"));
    remove(encode.getDefaultDest().c_str());
}

void testTwo() {
    string srcFile = "tests/data/input-1.txt";
    Encode encode(srcFile);
    assert(encode.getSrc() == srcFile);
    assert(encode.getDefaultDest() == srcFile + FILE_EXTENSION);
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
    assert(encode.getCodes() == expectedCodes);
    assert(encode.getLengths() == expectedLengths);
    assert(encode.getOffset() == 2);
    encode.toFile();
    assert(isEqual(encode.getDefaultDest(), "tests/data/output-1.txt"));
    remove(encode.getDefaultDest().c_str());
}

void testThree() {
    // TODO exception handling
}

int main() {
    cout << "encodeTests: Begin..." << endl;
    testOne();
    cout << "encodeTests: Passed Test 1" << endl;
    testTwo();
    cout << "encodeTests: Passed Test 2" << endl;
    testThree();
    cout << "encodeTests: Passed Test 3" << endl;
    cout << "encodeTests: ...Done" << endl;
    return 0;
}
