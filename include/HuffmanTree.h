#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "config.h"
#include <array>

struct HuffmanTreeNode {
        uint8_t *ascii;
        uint64_t count;
        HuffmanTreeNode *left, *right;
};

struct HuffmanTreeNodeComparator {
        bool operator()(HuffmanTreeNode *x, HuffmanTreeNode *y) const {
            return x->count > y->count;
        }
};

class HuffmanTree {
    private:
        std::array<uint64_t, CHAR_COUNT> frequencies;
        HuffmanTreeNode *root;
        void codesHelper(HuffmanTreeNode *node, uint64_t code, uint8_t length,
                         std::array<uint64_t, CHAR_COUNT> &codes,
                         std::array<uint8_t, CHAR_COUNT> &lengths);

    public:
        HuffmanTree(std::array<uint64_t, CHAR_COUNT> &frequencies);
        ~HuffmanTree();
        HuffmanTreeNode *getRoot();
        std::array<uint64_t, CHAR_COUNT> getFrequencies(),
            codes(std::array<uint8_t, CHAR_COUNT> &lengths);
        size_t depth();
};

#endif
