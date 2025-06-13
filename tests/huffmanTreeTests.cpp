#include "../src/HuffmanTree.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    unordered_map<unsigned char, uint64_t> map = {
        {'a', 1}, {'b', 2}, {'c', 4}, {'d', 8}};
    HuffmanTree actualTree = HuffmanTree{map};
    assert(actualTree.depth() == 3);
    HuffmanTreeNode *curr = actualTree.getRoot();
    assert(!curr->ascii && curr->count == 15 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<unsigned char>('d') &&
           curr->left->count == 8 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(!curr->ascii && curr->count == 7 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<unsigned char>('c') &&
           curr->left->count == 4 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(!curr->ascii && curr->count == 3 && curr->left && curr->right);
    assert(curr->left->ascii &&
           *(curr->left->ascii) == static_cast<unsigned char>('b') &&
           curr->left->count == 2 && !curr->left->left && !curr->left->right);
    curr = curr->right;
    assert(curr->ascii && *(curr->ascii) == static_cast<unsigned char>('a') &&
           curr->count == 1 && !curr->left && !curr->right);
    int actualLengths[arrSize];
    unordered_map<unsigned char, uint64_t> actualCodes =
        actualTree.codeTable(actualLengths);
    int expectedLengths[arrSize] = {};
    expectedLengths[static_cast<unsigned char>('a')] = 3;
    expectedLengths[static_cast<unsigned char>('b')] = 3;
    expectedLengths[static_cast<unsigned char>('c')] = 2;
    expectedLengths[static_cast<unsigned char>('d')] = 1;
    for (int i = 0; i < arrSize; i++) {
        assert(actualLengths[i] == expectedLengths[i]);
    }
    unordered_map<unsigned char, uint64_t> expectedCodes = {
        {'a', 7}, {'b', 6}, {'c', 2}, {'d', 0}};
    assert(actualCodes == expectedCodes);
}

int main() {
    testOne();
    cout << "huffmanTreeTests: PASSED" << endl;
    return 0;
}
