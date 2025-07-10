#include "../include/HuffmanTree.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    array<uint64_t, CHAR_COUNT> emptyArr = {};
    HuffmanTree huffmanTree(emptyArr);
    assert(!huffmanTree.getRoot());
    assert(huffmanTree.getFrequencies() == emptyArr);
    array<uint8_t, CHAR_COUNT> lengths;
    array<uint64_t, CHAR_COUNT> codes = huffmanTree.codes(lengths);
    assert((lengths == array<uint8_t, CHAR_COUNT>()));
    assert(codes == emptyArr);
    assert(huffmanTree.depth() == 0);
}

void testTwo() {
    array<uint64_t, CHAR_COUNT> oneElem = {1};
    HuffmanTree huffmanTree(oneElem);
    assert(huffmanTree.getRoot());
    assert(huffmanTree.getRoot()->ascii == 0);
    assert(huffmanTree.getRoot()->count == oneElem[0]);
    assert(!huffmanTree.getRoot()->left);
    assert(!huffmanTree.getRoot()->right);
    assert(huffmanTree.getFrequencies() == oneElem);
    array<uint8_t, CHAR_COUNT> lengths;
    array<uint64_t, CHAR_COUNT> codes = huffmanTree.codes(lengths);
    assert((lengths == array<uint8_t, CHAR_COUNT>{1}));
    assert((codes == array<uint64_t, CHAR_COUNT>()));
    assert(huffmanTree.depth() == 0);
}

void testThree() {
    array<uint64_t, CHAR_COUNT> counts = {};
    counts[static_cast<uint8_t>('a')] = 1;
    counts[static_cast<uint8_t>('b')] = 2;
    counts[static_cast<uint8_t>('c')] = 4;
    counts[static_cast<uint8_t>('d')] = 8;
    counts[static_cast<uint8_t>('\n')] = 1;
    HuffmanTree huffmanTree(counts);
    // TODO cont. input 1 test
}

int main() {
    cout << "huffmanTreeTests: Begin..." << endl;
    testOne();
    cout << "huffmanTreeTests: Passed Test 1" << endl;
    testTwo();
    cout << "huffmanTreeTests: Passed Test 2" << endl;
    testThree();
    cout << "huffmanTreeTests: Passed Test 3" << endl;
    cout << "huffmanTreeTests: ...Done" << endl;
    return 0;
}
