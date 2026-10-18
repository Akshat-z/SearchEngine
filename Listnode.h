#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef LISTNODE_H
#define LISTNODE_H

using namespace std;

class Listnode {
    Listnode *next; //next list item
    int id; //document id
    int count; //how many times occure in specific document.
    public:
       Listnode(int doc_id):id(doc_id),count(0) {next = NULL;};
       ~Listnode();
       void add(int doc_id);
       int getCount(int doc_id);
       int getDocumentCount();
};
#endif