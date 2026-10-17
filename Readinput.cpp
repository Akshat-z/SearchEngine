#include "Readinput.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int read_size(int *linecounter, int *maxlength, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error while opening file\n";
        return -1;
    }
    string line;
    while (getline(file, line)) {
        *maxlength = max(*maxlength, static_cast<int>(line.size() + 1));
        ++*linecounter;
    }
    if (*linecounter == 0 || *maxlength < 3) {
        cout << "Document is empty\n";
        return -1;
    }
    return 1;
}

static void split(const string &text, int id, TrieNode *trienode, Map *map) {
    cout<<"text: "<<text<<" "<<id<<endl;
    istringstream words(text);
    string token;
    int count = 0;
    while (words >> token) {
        trienode->insert(token, id);
        ++count;
    }
    map->setlength(id, count);
}

int read_input(Map *map, TrieNode *trienode, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error while opening file\n";
        return -1;
    }
    string line;
    for (int i = 0; i < map->getsize(); ++i) {
        if (!getline(file, line) || map->insert(line, i) == -1) {
            cout << "Invalid Document content\n";
            return -1;
        }
        split(map->getDocument(i), i, trienode, map);
    }
    return 1;
}
