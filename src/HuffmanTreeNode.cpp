#include "HuffmanTreeNode.h"

HuffmanTreeNode::HuffmanTreeNode(unsigned char *ascii, uint64_t count)
    : ascii(ascii), count(count) {}

unsigned char *HuffmanTreeNode::getAscii() { return this->ascii; }

uint64_t HuffmanTreeNode::getCount() { return this->count; }

HuffmanTreeNode *HuffmanTreeNode::getLeft() { return this->left; }

HuffmanTreeNode *HuffmanTreeNode::getRight() { return this->right; }
