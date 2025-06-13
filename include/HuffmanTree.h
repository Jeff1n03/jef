#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <cstdint>
#include <unordered_map>

constexpr int arrSize = 256;

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
        void codeTableHelper(HuffmanTreeNode *curr, int length, uint64_t code,
                             std::unordered_map<unsigned char, uint64_t> &codes,
                             int lengths[arrSize]);

    public:
        HuffmanTree(
            std::unordered_map<unsigned char, uint64_t> &frequencyTable);
        ~HuffmanTree();
        HuffmanTreeNode *getRoot();
        std::unordered_map<unsigned char, uint64_t> getFrequencyTable(),
            codeTable(int codeLengths[arrSize]);
        int depth();
};

#endif
