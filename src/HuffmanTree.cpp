#include "../include/HuffmanTree.h"
#include <queue>

using namespace std;
using HuffmanTreeNodePQ =
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                   HuffmanTreeNodeComparator>;

HuffmanTree::HuffmanTree(array<uint64_t, CHAR_COUNT> &frequencies)
    : frequencies(frequencies) {
    HuffmanTreeNodePQ pqueue;
    for (size_t i = 0; i < this->frequencies.size(); i++) {
        if (this->frequencies[i] > 0) {
            pqueue.push(new HuffmanTreeNode{
                new uint8_t(i), this->frequencies[i], nullptr, nullptr});
        }
    }
    if (pqueue.empty()) {
        pqueue.push(nullptr);
    } else if (pqueue.size() == 1) {
        pqueue.push(new HuffmanTreeNode{nullptr, 0, nullptr, nullptr});
    }
    while (pqueue.size() > 1) {
        HuffmanTreeNode *yin = pqueue.top();
        pqueue.pop();
        HuffmanTreeNode *yang = pqueue.top();
        pqueue.pop();
        HuffmanTreeNode *yinYang =
            new HuffmanTreeNode{nullptr, yin->count + yang->count, yang, yin};
        pqueue.push(yinYang);
    }
    this->root = pqueue.top();
}

HuffmanTree::~HuffmanTree() {
    if (root) {
        queue<HuffmanTreeNode *> q;
        q.push(this->root);
        while (!q.empty()) {
            HuffmanTreeNode *curr = q.front();
            q.pop();
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
            delete curr;
        }
    }
}

array<uint64_t, CHAR_COUNT> HuffmanTree::getFrequencies() {
    return this->frequencies;
}

HuffmanTreeNode *HuffmanTree::getRoot() { return this->root; }

int HuffmanTree::depth() {
    if (!root) {
        return 0;
    }
    queue<HuffmanTreeNode *> q;
    q.push(this->root);
    int height = 0;
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            HuffmanTreeNode *curr = q.front();
            q.pop();
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        height++;
    }
    return height - 1;
}

void HuffmanTree::codesHelper(HuffmanTreeNode *node, uint64_t code,
                              uint8_t length,
                              array<uint64_t, CHAR_COUNT> &codes,
                              array<uint8_t, CHAR_COUNT> &lengths) {
    if (!node) {
        return;
    }
    if (node->ascii) {
        codes[*(node->ascii)] = code;
        lengths[*(node->ascii)] = length;
        return;
    }
    if (!node->left && !node->right) {
        return;
    }
    if (node->left) {
        codesHelper(node->left, code << 1, length + 1, codes, lengths);
    }
    if (node->right) {
        codesHelper(node->right, (code << 1) | 1, length + 1, codes, lengths);
    }
}

array<uint64_t, CHAR_COUNT>
HuffmanTree::codes(array<uint8_t, CHAR_COUNT> &lengths) {
    lengths.fill(0);
    array<uint64_t, CHAR_COUNT> codes = {};
    codesHelper(this->root, 0, 0, codes, lengths);
    return codes;
}
