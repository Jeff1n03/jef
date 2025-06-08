#include "HuffmanTree.h"
#include "HuffmanTreeNode.h"
#include "HuffmanTreeNodeComparator.h"
#include <queue>
#include <vector>

using namespace std;
using HuffmanPQ = priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                                 HuffmanTreeNodeComparator>;

HuffmanTree::HuffmanTree(unordered_map<unsigned char, uint64_t> &frequencyTable)
    : frequencyTable(frequencyTable), root(generateTree()),
      depth(calculateDepth()) {}

HuffmanTreeNode *HuffmanTree::generateTree() {
    if (this->frequencyTable.empty()) {
        return nullptr;
    }
    HuffmanPQ pqueue;
    for (const auto &pair : this->frequencyTable) {
        pqueue.push(
            new HuffmanTreeNode{new unsigned char{pair.first}, pair.second});
    }
    if (pqueue.size() == 1) {
        pqueue.push(new HuffmanTreeNode{nullptr, 0});
    }
    while (pqueue.size() > 1) {
        HuffmanTreeNode *yin = pqueue.top();
        pqueue.pop();
        HuffmanTreeNode *yang = pqueue.top();
        pqueue.pop();
        HuffmanTreeNode *yinYang =
            new HuffmanTreeNode{nullptr, yin->count + yang->count};
        yinYang->left = yang;
        yinYang->right = yin;
        pqueue.push(yinYang);
    }
    return pqueue.top();
}

uint8_t HuffmanTree::calculateDepth() {
    if (!root) {
        return 0;
    }
    queue<HuffmanTreeNode *> q;
    q.push(this->root);
    uint8_t height = 0;
    while (!q.empty()) {
        uint8_t levelSize = q.size();
        for (uint8_t i = 0; i < levelSize; i++) {
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

HuffmanTreeNode *HuffmanTree::getRoot() { return this->root; }

uint8_t HuffmanTree::getDepth() { return this->depth; }
