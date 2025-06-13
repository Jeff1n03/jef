#include "../include/HuffmanTree.h"
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

unordered_map<unsigned char, uint64_t> HuffmanTree::getFrequencyTable() {
    return this->frequencyTable;
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

void HuffmanTree::codeTableHelper(HuffmanTreeNode *curr, int length,
                                  uint64_t code,
                                  unordered_map<unsigned char, uint64_t> &codes,
                                  uint8_t lengths[arrSize]) {
    if (curr->ascii) {
        lengths[*(curr->ascii)] = length;
        codes[*(curr->ascii)] = code;
        return;
    }
    if (!curr->left && !curr->right) {
        return;
    }
    if (curr->left) {
        codeTableHelper(curr->left, length + 1, code << 1, codes, lengths);
    }
    if (curr->right) {
        codeTableHelper(curr->right, length + 1, (code << 1) | 1, codes,
                        lengths);
    }
}

unordered_map<unsigned char, uint64_t>
HuffmanTree::codeTable(uint8_t codeLengths[arrSize]) {
    memset(codeLengths, 0, arrSize);
    unordered_map<unsigned char, uint64_t> codes = this->frequencyTable;
    codeTableHelper(this->root, 0, 0, codes, codeLengths);
    return codes;
}
