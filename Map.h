#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map {
private:
    vector<string> documents;
    vector<int> lengths;
    int buffersize;

public:
    Map(int size, int buffersize);
    int insert(const string &line, int i);
    void setlength(int id, int length) { lengths[id] = length; }
    int getlength(int id) const { return lengths[id]; }
    void print(int i) const { cout << i << " " << documents[i] << endl; }
    const string &getDocument(int i) const { return documents[i]; }
    int getsize() const { return static_cast<int>(documents.size()); }
    int getbuffersize() const { return buffersize; }
};

#endif
