#include "Trienode.h"

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
            cout<<"Add to list "<<token<<endl;
            if (list == NULL) {
                list = new Listnode(doc_id);
            }
            list->add(doc_id);
        }
    } else {
        if (sibling == nullptr) sibling = new TrieNode();
        sibling->insert(token, doc_id, position);
    }
}

int TrieNode::tfsearchword(int i, string word, int position) {
    if (word.empty() || position >= (int)word.size()) return 0;

    cout << "Looking for " << word[position] << ", checking " << value << endl;

    if (value != word[position]) {
        if (sibling == nullptr) {
            cout << "Word not found" << endl;
            return 0;
        }
        return sibling->tfsearchword(i, word, position);
    }

    if (position == (int)word.size() - 1) {
        return list->getCount(i);
    }

    if (child == nullptr) {
        cout << "Word not found" << endl;
        return 0;
    }
    return child->tfsearchword(i, word, position + 1);
}