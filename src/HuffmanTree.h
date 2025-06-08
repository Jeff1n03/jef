#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanTreeNode.h"
#include <unordered_map>

class HuffmanTree {
    private:
        std::unordered_map<unsigned char, uint64_t> frequencyTable;
        HuffmanTreeNode *root, *generateTree();
        uint8_t depth, calculateDepth();

    public:
        HuffmanTree(
            std::unordered_map<unsigned char, uint64_t> &frequencyTable);
        // TODO destructor
        HuffmanTreeNode *getRoot();
        uint8_t getDepth();
};

#endif
