#ifndef HUFFMAN_TREE_NODE_COMPARATOR_H
#define HUFFMAN_TREE_NODE_COMPARATOR_H

#include "HuffmanTreeNode.h"

class HuffmanTreeNodeComparator {
    public:
        bool operator()(HuffmanTreeNode *x, HuffmanTreeNode *y) const {
            return x->getCount() > y->getCount();
        }
};

#endif
