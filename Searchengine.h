#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include "Readinput.h"
#include "Map.h"
#include "Trienode.h"
#include "Search.h"

using namespace std;

int inputmanage(const string &input, TrieNode *trienode, Map *map, int k);

#endif
