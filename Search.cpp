#include "Search.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

static void toLower(string &s) {
    for (size_t j = 0; j < s.size(); ++j)
        s[j] = static_cast<char>(tolower(static_cast<unsigned char>(s[j])));
}

struct Result {
    int doc;
    int score;
};

// true if a is a better result than b: higher score first, then lower doc id
static bool better(const Result &a, const Result &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.doc < b.doc;
}

// priority_queue keeps the "largest" element on top; with this comparator the WORST result is on top
struct WorstOnTop {
    bool operator()(const Result &a, const Result &b) const { return better(a, b); }
};

static bool docLess(const Posting &p, int doc) { return p.doc < doc; }

/*
/search w1 w2 ...
documents containing ALL words, score = sum of the words' counts in the document, best k printed
*/
void search(const string &token, TrieNode *trienode, Map *map, int k) {
    istringstream input(token);
    string command, word;
    input >> command;

    // 1. collect the posting list of every distinct word
    set<string> seen;
    vector<const vector<Posting> *> lists;
    while (input >> word) {
        toLower(word);
        if (!seen.insert(word).second) continue; // duplicate query word
        const vector<Posting> *postings = trienode->getPostings(word);
        if (postings == nullptr) { // one word is nowhere, so no document has all words
            cout << "No documents found" << endl;
            return;
        }
        lists.push_back(postings);
    }
    if (lists.empty()) {
        cout << "Invalid /search command: expected /search <word> [<word> ...]\n";
        return;
    }

    // 2. walk the shortest list, binary search the doc in all the other lists
    size_t shortest = 0;
    for (size_t i = 1; i < lists.size(); ++i)
        if (lists[i]->size() < lists[shortest]->size()) shortest = i;

    // 3. keep only the k best results
    priority_queue<Result, vector<Result>, WorstOnTop> best;
    const vector<Posting> &base = *lists[shortest];
    for (size_t i = 0; i < base.size(); ++i) {
        Result r = {base[i].doc, base[i].tf};
        bool inAll = true;
        for (size_t j = 0; j < lists.size() && inAll; ++j) {
            if (j == shortest) continue;
            vector<Posting>::const_iterator it =
                lower_bound(lists[j]->begin(), lists[j]->end(), r.doc, docLess);
            if (it == lists[j]->end() || it->doc != r.doc) inAll = false;
            else r.score += it->tf;
        }
        if (!inAll) continue;
        if (static_cast<int>(best.size()) < k) {
            best.push(r);
        } else if (k > 0 && better(r, best.top())) {
            best.pop();
            best.push(r);
        }
    }

    // 4. heap gives worst first, so fill the vector from the back
    vector<Result> results(best.size());
    for (size_t i = results.size(); i > 0; --i) {
        results[i - 1] = best.top();
        best.pop();
    }
    if (results.empty()) {
        cout << "No documents found" << endl;
        return;
    }
    for (size_t i = 0; i < results.size(); ++i)
        cout << results[i].doc << " " << results[i].score << " " << map->getDocument(results[i].doc) << endl;
}

void df(const string &token, TrieNode *trienode) {
    istringstream input(token);
    string command, term, extra;
    if (!(input >> command >> term) || input >> extra || command != "/df") {
        cout << "Invalid /df command: expected /df <string>\n";
        return;
    }

    toLower(term);
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
    toLower(term);
    cout<<number<< " "<< term << " "<< trienode->tfsearchword(value, term, 0) <<endl;
    return 0;
}

//4:14:06