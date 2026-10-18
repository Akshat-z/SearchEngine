#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include "Trienode.h"
#include "Map.h"

using namespace std;

void search(const string &token, TrieNode *trienode, Map *map, int k);
void df(const string &token, TrieNode *trienode);
int tf(const string &token, TrieNode *trienode);

#endif
