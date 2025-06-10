#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <unordered_map>

struct HuffmanTreeNode {
        unsigned char *ascii;
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
        std::unordered_map<unsigned char, uint64_t> frequencyTable;
        HuffmanTreeNode *root;

    public:
        HuffmanTree(
            std::unordered_map<unsigned char, uint64_t> &frequencyTable);
        // TODO destructor
        HuffmanTreeNode *getRoot();
        std::unordered_map<unsigned char, uint64_t> getFrequencyTable();
        uint8_t depth();
};

#endif
