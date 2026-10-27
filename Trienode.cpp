#include "Trienode.h"
#include <algorithm>

using namespace std;

TrieNode::TrieNode() : sibling(nullptr), child(nullptr), value(-1) {}

TrieNode::~TrieNode() {
    delete child;
    delete sibling;
}

void TrieNode::insert(const string &token, int doc_id, size_t position) {
    if (position >= token.size()) return;
    if (value == -1 || value == token[position]) {
        value = token[position];
        if (position + 1 < token.size()) {
            if (child == nullptr) child = new TrieNode();
            child->insert(token, doc_id, position + 1);
        }
        if (token.size()-1 == position) {
            if (!postings.empty() && postings.back().doc == doc_id) ++postings.back().tf;
            else postings.push_back({doc_id, 1});
        }
    } else {
        if (sibling == nullptr) sibling = new TrieNode();
        sibling->insert(token, doc_id, position);
    }
}

int TrieNode::dfsearchword(const string &word, size_t position) {
    if (word.empty() || position >= word.size()) return 0;
    if (value != word[position])
        return sibling == nullptr ? 0 : sibling->dfsearchword(word, position);
    if (position + 1 == word.size())
        return static_cast<int>(postings.size());
    return child == nullptr ? 0 : child->dfsearchword(word, position + 1);
}

int TrieNode::tfsearchword(int i, string word, int position) {
    if (word.empty() || position >= (int)word.size()) return 0;

    if (value != word[position]) {
        if (sibling == nullptr) {
            cout << "Word not found" << endl;
            return 0;
        }
        return sibling->tfsearchword(i, word, position);
    }
    if (position == (int)word.size() - 1) {
        vector<Posting>::const_iterator it = lower_bound(postings.begin(), postings.end(), i,
            [](const Posting &p, int doc) { return p.doc < doc; });
        return it != postings.end() && it->doc == i ? it->tf : 0;
    }

    if (child == nullptr) {
        cout << "Word not found" << endl;
        return 0;
    }
    return child->tfsearchword(i, word, position + 1);
}

const vector<Posting> *TrieNode::getPostings(const string &word) const {
    const TrieNode *node = this;
    for (size_t pos = 0; pos < word.size(); ++pos) {
        while (node != nullptr && node->value != word[pos]) node = node->sibling;
        if (node == nullptr) return nullptr;
        if (pos + 1 == word.size()) return node->postings.empty() ? nullptr : &node->postings;
        node = node->child;
    }
    return nullptr;
}


void TrieNode::printFullTree(const string &prefix) const {
    // go through this letter and all its siblings; recurse into each child
    const TrieNode *node = this;
    while (node != nullptr) {
        if (node->value != -1) { // -1 is the empty root of an empty trie
            const string word = prefix + node->value;
            if (!node->postings.empty()) {
                cout << word << ":";
                for (size_t i = 0; i < node->postings.size(); ++i)
                    cout << " (doc " << node->postings[i].doc << ", tf " << node->postings[i].tf << ")";
                cout << endl;
            }
            if (node->child != nullptr) node->child->printFullTree(word);
        }
        cout<<"prefix: "<<prefix<<"\n";
        node = node->sibling;
    }
}