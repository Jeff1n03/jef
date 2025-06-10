#include "HuffmanTree.h"
#include <queue>

using namespace std;
using HuffmanTreeNodePQ =
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                   HuffmanTreeNodeComparator>;

HuffmanTree::HuffmanTree(unordered_map<unsigned char, uint64_t> &frequencyTable)
    : frequencyTable(frequencyTable) {
    if (this->frequencyTable.empty()) {
        this->root = nullptr;
    } else {
        HuffmanTreeNodePQ pqueue;
        for (const auto &pair : this->frequencyTable) {
            pqueue.push(new HuffmanTreeNode{new unsigned char{pair.first},
                                            pair.second, nullptr, nullptr});
        }
        if (pqueue.size() == 1) {
            pqueue.push(new HuffmanTreeNode{nullptr, 0, nullptr, nullptr});
        }
        while (pqueue.size() > 1) {
            HuffmanTreeNode *yin = pqueue.top();
            pqueue.pop();
            HuffmanTreeNode *yang = pqueue.top();
            pqueue.pop();
            HuffmanTreeNode *yinYang = new HuffmanTreeNode{
                nullptr, yin->count + yang->count, yang, yin};
            pqueue.push(yinYang);
        }
        this->root = pqueue.top();
    }
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

HuffmanTreeNode *HuffmanTree::getRoot() { return this->root; }

unordered_map<unsigned char, uint64_t> HuffmanTree::getFrequencyTable() {
    return this->frequencyTable;
}

uint8_t HuffmanTree::depth() {
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
