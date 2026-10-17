#include "Searchengine.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int inputmanage(const string &input, TrieNode *trienode, Map *map, int k) {
    const size_t last = input.find_last_not_of(" \t\n");
    string cmd = input;
    cmd.erase(last+1);
    if (cmd.rfind("/search", 0) == 0) {
        search(cmd, trienode, map, k);
    } else if (cmd == "/df") {
        df(trienode);
    } else if (cmd.rfind("/tf", 0) == 0) {
        return tf(cmd, trienode);
    } else if (cmd == "/exit") {
        cout<<"Exiting ..."<<endl;
        return 2;
    } else {
        cout<<"Invalid cmd\n";
        return -1;
    }
    return 1;

}

int main(int argc, char **argv) {
    if (argc != 5 || string(argv[1]) != "-d" || string(argv[3]) != "-k") {
        cout << "Wrong arguments" << endl;
        return 1;
    }
    int linecounter = 0;
    int maxlength = 0;
    const string filename(argv[2]);
    const int k = stoi(argv[4]);
    if (k < 0 || read_size(&linecounter, &maxlength, filename) == -1) return 1;

    Map map(linecounter, maxlength);
    TrieNode trienode;
    if (read_input(&map, &trienode, filename) == -1) return 1;
    cout << "Database Ready" << endl;

    string input;
    while (getline(cin, input)) {
        int r = inputmanage(input, &trienode, &map, k);
        if (r == 2) {
            return 0;
        }
    }
    return 0;
}
