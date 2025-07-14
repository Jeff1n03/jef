#include "../include/Decode.h"
#include "testUtils.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    string srcFile = "tests/data/output-0.txt";
    Decode decode(srcFile);
    assert(decode.getSrc() == srcFile);
    assert(decode.getDefaultDest() ==
           srcFile.substr(0, srcFile.size() - strlen(FILE_EXTENSION)));
    assert((decode.getCodes() == array<uint64_t, CHAR_COUNT>()));
    assert((decode.getLengths() == array<uint8_t, CHAR_COUNT>()));
    assert(decode.getOffset() == 0);
    decode.toFile();
    assert(isEqual(decode.getDefaultDest(), "tests/data/input-0.txt"));
    remove(decode.getDefaultDest().c_str());
}

void testTwo() {
    string srcFile = "tests/data/output-1.txt";
    Decode decode(srcFile);
    assert(decode.getSrc() == srcFile);
    assert(decode.getDefaultDest() ==
           srcFile.substr(0, srcFile.size() - strlen(FILE_EXTENSION)));
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
    assert(decode.getCodes() == expectedCodes);
    assert(decode.getLengths() == expectedLengths);
    assert(decode.getOffset() == 2);
    decode.toFile();
    assert(isEqual(decode.getDefaultDest(), "tests/data/input-1.txt"));
    remove(decode.getDefaultDest().c_str());
}

void testThree() {
    // TODO exception handling
}

int main() {
    cout << "decodeTests: Begin..." << endl;
    testOne();
    cout << "decodeTests: Passed Test 1" << endl;
    testTwo();
    cout << "decodeTests: Passed Test 2" << endl;
    testThree();
    cout << "decodeTests: Passed Test 3" << endl;
    cout << "decodeTests: ...Done" << endl;
    return 0;
}
