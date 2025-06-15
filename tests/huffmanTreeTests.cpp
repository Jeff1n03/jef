#include "../include/HuffmanTree.h"
#include <cassert>
#include <iostream>

using namespace std;

void testOne() {
    unordered_map<unsigned char, uint64_t> map = {
        {'a', 1}, {'b', 2}, {'c', 4}, {'d', 8}};
    HuffmanTree huffmanTree = HuffmanTree{map};
    assert(huffmanTree.depth() == 3);
    HuffmanTreeNode *curr = huffmanTree.getRoot();
    assert(curr);
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
    uint8_t actualLengths[arrSize];
    unordered_map<unsigned char, uint64_t> actualCodes =
        huffmanTree.codeTable(actualLengths);
    uint8_t expectedLengths[arrSize] = {};
    expectedLengths[static_cast<unsigned char>('a')] = 3;
    expectedLengths[static_cast<unsigned char>('b')] = 3;
    expectedLengths[static_cast<unsigned char>('c')] = 2;
    expectedLengths[static_cast<unsigned char>('d')] = 1;
    for (size_t i = 0; i < arrSize; i++) {
        assert(actualLengths[i] == expectedLengths[i]);
    }
    unordered_map<unsigned char, uint64_t> expectedCodes = {
        {'a', 7}, {'b', 6}, {'c', 2}, {'d', 0}};
    assert(actualCodes == expectedCodes);
}

void testTwo() {
    unordered_map<unsigned char, uint64_t> map = {{'a', 1}, {'b', 1}};
    HuffmanTree huffmanTree = HuffmanTree{map};
    assert(huffmanTree.depth() == 1);
    HuffmanTreeNode *root = huffmanTree.getRoot();
    assert(root);
    assert(!root->ascii && root->count == 2 && root->left && root->right);
    HuffmanTreeNode *left = root->left;
    assert(left->ascii && left->count == 1 && !left->left && !left->right);
    assert(*(left->ascii) == static_cast<unsigned char>('a') ||
           *(left->ascii) == static_cast<unsigned char>('b'));
    HuffmanTreeNode *right = root->right;
    assert(right->ascii && right->count == 1 && !right->left && !right->right);
    assert(*(right->ascii) == static_cast<unsigned char>('a') ||
           *(right->ascii) == static_cast<unsigned char>('b'));
    uint8_t lengths[arrSize];
    unordered_map<unsigned char, uint64_t> codes =
        huffmanTree.codeTable(lengths);
    for (size_t i = 0; i < arrSize; i++) {
        if (i == static_cast<unsigned char>('a')) {
            assert(lengths[i] == 1);
        } else if (i == static_cast<unsigned char>('b')) {
            assert(lengths[i] == 1);
        } else {
            assert(lengths[i] == 0);
        }
    }
    unordered_map<unsigned char, uint64_t> caseOne = {{'a', 0}, {'b', 1}};
    unordered_map<unsigned char, uint64_t> caseTwo = {{'a', 1}, {'b', 0}};
    assert(codes == caseOne || codes == caseTwo);
}

void testThree() {
    unordered_map<unsigned char, uint64_t> map = {{'\0', 1}};
    HuffmanTree huffmanTree = HuffmanTree{map};
    assert(huffmanTree.depth() == 1);
    HuffmanTreeNode *root = huffmanTree.getRoot();
    assert(root);
    assert(!root->ascii && root->count == 1 && root->left && root->right);
    HuffmanTreeNode *left = root->left;
    assert(left->ascii && *(left->ascii) == static_cast<unsigned char>('\0') &&
           left->count == 1 && !left->left && !left->right);
    HuffmanTreeNode *right = root->right;
    assert(!right->ascii && right->count == 0 && !right->left && !right->right);
    uint8_t lengths[arrSize];
    unordered_map<unsigned char, uint64_t> actualCodes =
        huffmanTree.codeTable(lengths);
    for (size_t i = 0; i < arrSize; i++) {
        if (i == static_cast<unsigned char>('\0')) {
            assert(lengths[i] == 1);
        } else {
            assert(lengths[i] == 0);
        }
    }
    unordered_map<unsigned char, uint64_t> expectedCodes = {{'\0', 0}};
    assert(actualCodes == expectedCodes);
}

void testFour() {
    unordered_map<unsigned char, uint64_t> map;
    HuffmanTree huffmanTree = HuffmanTree{map};
    assert(huffmanTree.depth() == 0);
    assert(!huffmanTree.getRoot());
    uint8_t lengths[arrSize];
    unordered_map<unsigned char, uint64_t> codes =
        huffmanTree.codeTable(lengths);
    for (size_t i = 0; i < arrSize; i++) {
        assert(lengths[i] == 0);
    }
    assert(codes == map);
}

int main() {
    cout << "\nhuffmanTreeTests: Begin..." << endl;
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
