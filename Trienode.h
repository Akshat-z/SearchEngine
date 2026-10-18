#ifndef TRIENODE_H
#define TRIENODE_H

#include <string>
#include<vector>
#include<iostream>
#include "Listnode.h"

using namespace std;

class TrieNode {
    TrieNode *sibling;
    TrieNode *child;
    Listnode *list;
    char value;
public:
    TrieNode();
    ~TrieNode();
    void insert(const string &token, int i, size_t position = 0);
    int tfsearchword(int i, string word, int position);
    int dfsearchword(const string &word, size_t position = 0);
};

#endif
