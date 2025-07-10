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

void testThreeHelper(HuffmanTreeNode *curr) {
    assert(curr);
    assert(curr->ascii == static_cast<uint8_t>('\n'));
    assert(curr->count == 16);
    assert(curr->left && curr->right);
    assert(curr->right->ascii == static_cast<uint8_t>('d'));
    assert(curr->right->count == 8);
    assert(!curr->right->left && !curr->right->right);
    curr = curr->left;
    assert(curr);
    assert(curr->ascii == static_cast<uint8_t>('\n'));
    assert(curr->count == 8);
    assert(curr->left && curr->right);
    assert(curr->right->ascii == static_cast<uint8_t>('c'));
    assert(curr->right->count == 4);
    assert(!curr->right->left && !curr->right->right);
    curr = curr->left;
    assert(curr);
    assert(curr->ascii == static_cast<uint8_t>('\n'));
    assert(curr->count == 4);
    assert(curr->left && curr->right);
    assert(curr->right->ascii == static_cast<uint8_t>('b'));
    assert(curr->right->count == 2);
    assert(!curr->right->left && !curr->right->right);
    curr = curr->left;
    assert(curr);
    assert(curr->ascii == static_cast<uint8_t>('\n'));
    assert(curr->count == 2);
    assert(curr->left && curr->right);
    assert(curr->left->ascii == static_cast<uint8_t>('\n'));
    assert(curr->left->count == 1);
    assert(!curr->left->left && !curr->left->right);
    assert(curr->right->ascii == static_cast<uint8_t>('a'));
    assert(curr->right->count == 1);
    assert(!curr->right->left && !curr->right->right);
}

void testThree() {
    array<uint64_t, CHAR_COUNT> counts = {};
    counts[static_cast<uint8_t>('a')] = 1;
    counts[static_cast<uint8_t>('b')] = 2;
    counts[static_cast<uint8_t>('c')] = 4;
    counts[static_cast<uint8_t>('d')] = 8;
    counts[static_cast<uint8_t>('\n')] = 1;
    HuffmanTree huffmanTree(counts);
    testThreeHelper(huffmanTree.getRoot());
    assert(huffmanTree.getFrequencies() == counts);
    array<uint8_t, CHAR_COUNT> actualLengths;
    array<uint64_t, CHAR_COUNT> actualCodes = huffmanTree.codes(actualLengths);
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    array<uint64_t, CHAR_COUNT> expectedCodes = {};
    expectedLengths[static_cast<uint8_t>('a')] = 4;
    expectedCodes[static_cast<uint8_t>('a')] = 0b0001;
    expectedLengths[static_cast<uint8_t>('b')] = 3;
    expectedCodes[static_cast<uint8_t>('b')] = 0b001;
    expectedLengths[static_cast<uint8_t>('c')] = 2;
    expectedCodes[static_cast<uint8_t>('c')] = 0b01;
    expectedLengths[static_cast<uint8_t>('d')] = 1;
    expectedCodes[static_cast<uint8_t>('d')] = 0b1;
    expectedLengths[static_cast<uint8_t>('\n')] = 4;
    expectedCodes[static_cast<uint8_t>('\n')] = 0b0000;
    assert(actualLengths == expectedLengths);
    assert(actualCodes == expectedCodes);
    assert(huffmanTree.depth() == 4);
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
