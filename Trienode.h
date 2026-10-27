#ifndef TRIENODE_H
#define TRIENODE_H

#include <string>
#include<vector>
#include<iostream>

using namespace std;

// posting list entry (inverted index): doc id and term count in that doc
struct Posting { int doc; int tf; };

class TrieNode {
    TrieNode *sibling;
    TrieNode *child;
    vector<Posting> postings; // sorted by doc id, since docs are inserted in order
    char value;
public:
    TrieNode();
    ~TrieNode();
    void insert(const string &token, int i, size_t position = 0);
    int tfsearchword(int i, string word, int position);
    const vector<Posting> *getPostings(const string &word) const; 
    int dfsearchword(const string &word, size_t position = 0);
    void printFullTree(const string &prefix = "") const; // prints every word with its postings
};

#endif
