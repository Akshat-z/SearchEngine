#ifndef READINPUT_H
#define READINPUT_H

#include <string>
#include "Map.h"
#include "Trienode.h"

using namespace std;

int read_size(int *linecounter, int *maxlength, const string &filename);
int read_input(Map *map, TrieNode *trienode, const string &filename);

#endif
