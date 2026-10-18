#include "Listnode.h"

Listnode::~Listnode() {
    if (next != NULL) {
        delete(next);
    }
}

void Listnode::add(int doc_id) {
    if (doc_id == id) {
        count++;
    } else {
        if(next == NULL) {
            next = new Listnode(doc_id);
        }
        next->add(doc_id);
    }
}

int Listnode::getCount(int doc_id) {
    for (Listnode *node = this; node != NULL; node = node->next) {
        if (node->id == doc_id) return node->count;
    }
    return 0;
}

int Listnode::getDocumentCount(){
    int count = 0;
    for (const Listnode *node = this; node != NULL; node = node->next) ++count;
    return count;
}