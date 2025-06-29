#include "../include/HuffmanTree.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    array<uint64_t, CHAR_COUNT> frequencies = {};
    frequencies[static_cast<uint8_t>('a')] = 1;
    frequencies[static_cast<uint8_t>('b')] = 2;
    frequencies[static_cast<uint8_t>('c')] = 4;
    frequencies[static_cast<uint8_t>('d')] = 8;
    HuffmanTree huffmanTree(frequencies);
    assert(huffmanTree.depth() == 3);
    HuffmanTreeNode *curr = huffmanTree.getRoot();
    assert(curr);
    assert(!curr->ascii && curr->count == 15 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<uint8_t>('d') &&
           curr->left->count == 8 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(!curr->ascii && curr->count == 7 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<uint8_t>('c') &&
           curr->left->count == 4 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(!curr->ascii && curr->count == 3 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<uint8_t>('b') &&
           curr->left->count == 2 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(curr->ascii && *(curr->ascii) == static_cast<uint8_t>('a') &&
           curr->count == 1 && !curr->left && !curr->right);
    array<uint8_t, CHAR_COUNT> actualLengths;
    array<uint64_t, CHAR_COUNT> actualCodes = huffmanTree.codes(actualLengths);
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    expectedLengths[static_cast<uint8_t>('a')] = 3;
    expectedLengths[static_cast<uint8_t>('b')] = 3;
    expectedLengths[static_cast<uint8_t>('c')] = 2;
    expectedLengths[static_cast<uint8_t>('d')] = 1;
    array<uint64_t, CHAR_COUNT> expectedCodes = {};
    expectedCodes[static_cast<uint8_t>('a')] = 7;
    expectedCodes[static_cast<uint8_t>('b')] = 6;
    expectedCodes[static_cast<uint8_t>('c')] = 2;
    expectedCodes[static_cast<uint8_t>('d')] = 0;
    assert(actualCodes == expectedCodes);
    assert(actualLengths == expectedLengths);
}

void testTwo() {
    array<uint64_t, CHAR_COUNT> frequencies = {};
    frequencies[static_cast<uint8_t>('a')] = 1;
    frequencies[static_cast<uint8_t>('b')] = 1;
    HuffmanTree huffmanTree(frequencies);
    assert(huffmanTree.depth() == 1);
    HuffmanTreeNode *root = huffmanTree.getRoot();
    assert(root);
    assert(!root->ascii && root->count == 2 && root->left && root->right);
    HuffmanTreeNode *left = root->left;
    assert(left->ascii && left->count == 1 && !left->left && !left->right);
    assert(*(left->ascii) == static_cast<uint8_t>('a') ||
           *(left->ascii) == static_cast<uint8_t>('b'));
    HuffmanTreeNode *right = root->right;
    assert(right->ascii && right->count == 1 && !right->left && !right->right);
    assert(*(right->ascii) == static_cast<uint8_t>('a') ||
           *(right->ascii) == static_cast<uint8_t>('b'));
    array<uint8_t, CHAR_COUNT> actualLengths;
    array<uint64_t, CHAR_COUNT> actualCodes = huffmanTree.codes(actualLengths);
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    expectedLengths[static_cast<uint8_t>('a')] = 1;
    expectedLengths[static_cast<uint8_t>('b')] = 1;
    array<uint64_t, CHAR_COUNT> expectedCodes1 = {};
    expectedCodes1[static_cast<uint8_t>('a')] = 0;
    expectedCodes1[static_cast<uint8_t>('b')] = 1;
    array<uint64_t, CHAR_COUNT> expectedCodes2 = {};
    expectedCodes2[static_cast<uint8_t>('a')] = 1;
    expectedCodes2[static_cast<uint8_t>('b')] = 0;
    assert(actualCodes == expectedCodes1 || actualCodes == expectedCodes2);
    assert(actualLengths == expectedLengths);
}

void testThree() {
    array<uint64_t, CHAR_COUNT> frequencies = {};
    frequencies[static_cast<uint8_t>('\0')] = 1;
    HuffmanTree huffmanTree(frequencies);
    assert(huffmanTree.depth() == 1);
    HuffmanTreeNode *root = huffmanTree.getRoot();
    assert(root);
    assert(!root->ascii && root->count == 1 && root->left && root->right);
    HuffmanTreeNode *left = root->left;
    assert(left->ascii && *(left->ascii) == static_cast<uint8_t>('\0') &&
           left->count == 1 && !left->left && !left->right);
    HuffmanTreeNode *right = root->right;
    assert(!right->ascii && right->count == 0 && !right->left && !right->right);
    array<uint8_t, CHAR_COUNT> actualLengths;
    array<uint64_t, CHAR_COUNT> actualCodes = huffmanTree.codes(actualLengths);
    array<uint8_t, CHAR_COUNT> expectedLengths = {};
    expectedLengths[static_cast<uint8_t>('\0')] = 1;
    array<uint64_t, CHAR_COUNT> expectedCodes = {};
    expectedCodes[static_cast<uint8_t>('\0')] = 0;
    assert(actualCodes == expectedCodes);
    assert(actualLengths == expectedLengths);
}

void testFour() {
    array<uint64_t, CHAR_COUNT> frequencies = {};
    HuffmanTree huffmanTree(frequencies);
    assert(huffmanTree.depth() == 0);
    assert(!huffmanTree.getRoot());
    array<uint8_t, CHAR_COUNT> lengths = {0, 1, 2, 3};
    array<uint64_t, CHAR_COUNT> codes = huffmanTree.codes(lengths);
    assert(codes == frequencies);
    assert((lengths == array<uint8_t, CHAR_COUNT>{}));
}

int main() {
    cout << "huffmanTreeTests: Begin..." << endl;
    testOne();
    cout << "huffmanTreeTests: Passed Test 1" << endl;
    testTwo();
    cout << "huffmanTreeTests: Passed Test 2" << endl;
    testThree();
    cout << "huffmanTreeTests: Passed Test 3" << endl;
    testFour();
    cout << "huffmanTreeTests: Passed Test 4" << endl;
    cout << "huffmanTreeTests: ...Done" << endl;
    return 0;
}
