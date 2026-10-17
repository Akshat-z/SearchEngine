#include "Map.h"
#include <sstream>

using namespace std;

Map::Map(int size, int buffersize)
    : documents(size), lengths(size, 0), buffersize(buffersize) {}

int Map::insert(const string &line, int i) {
    if (i < 0 || i >= getsize()) return -1;
    istringstream input(line);
    int id;
    if (!(input >> id) || id != i) return -1;
    getline(input, documents[i]);
    const size_t first = documents[i].find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        documents[i].clear();
        return -1;
    }
    documents[i].erase(0, first);
    const size_t last = documents[i].find_last_not_of(" \t\r\n");
    documents[i].erase(last + 1);
    return 1;
}
