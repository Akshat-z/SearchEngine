#include "Search.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

void search(const string &, TrieNode *, Map *, int) {
}

void df(const string &token, TrieNode *trienode) {
    istringstream input(token);
    string command, term, extra;
    if (!(input >> command >> term) || input >> extra || command != "/df") {
        cout << "Invalid /df command: expected /df <string>\n";
        return;
    }

    for (size_t j = 0; j < term.size(); ++j) term[j] = static_cast<char>(tolower(static_cast<unsigned char>(term[j])));
    cout << term << " " << trienode->dfsearchword(term) << endl;
}

/*
count of word w present in the documnet with index x
/tf x w
*/
int tf(const string &token, TrieNode *trienode) {
    istringstream input(token);
    string command, number, term, extra;

    // Read the three required parts. A fourth part means the command is invalid.
    if (!(input >> command >> number >> term) || input >> extra || command != "/tf") {
        cout << "Invalid /tf command: expected /tf <int> <string>\n";
        return -1;
    }

    // Check that the second part contains only an integer.
    istringstream numberInput(number);
    int value;
    string leftover;
    if (!(numberInput >> value) || numberInput >> leftover) {
        cout << "Invalid /tf command: expected /tf <int> <string>\n";
        return -1;
    }
    for (size_t j = 0; j < term.size(); ++j) term[j] = static_cast<char>(tolower(static_cast<unsigned char>(term[j])));
    cout<<number<< " "<< term << " "<< trienode->tfsearchword(value, term, 0) <<endl;
    return 0;
}

//4:14:06