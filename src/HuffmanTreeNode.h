#ifndef HUFFMAN_TREE_NODE_H
#define HUFFMAN_TREE_NODE_H

#include <cstdint>

class HuffmanTree;

class HuffmanTreeNode {
    private:
        unsigned char *ascii;
        uint64_t count;
        HuffmanTreeNode *left, *right;

        friend class HuffmanTree;

    public:
        HuffmanTreeNode(unsigned char *ascii, uint64_t count);
        unsigned char *getAscii();
        uint64_t getCount();
        HuffmanTreeNode *getLeft(), *getRight();
};

#endif
