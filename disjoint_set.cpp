//
// Created by Noah Feinberg on 10/11/2022.
//

#include "disjoint_set.h"
#include <iostream>

void disjoint_set::add_node(int vertex) {
    node n{nullptr, 1, vertex};
    node_array[vertex] = n;
}

node* disjoint_set::find(node* n) {
    if (n->pointer != nullptr) {
        n->pointer = find(n->pointer);
        return n->pointer;
    } else {
        return n;
    }
}

node* disjoint_set::find(int vertex) {
    return find(&node_array[vertex]);
}

void disjoint_set::merge(node* n1, node* n2) {
    n1 = find(n1);
    n2 = find(n2);
    if (n1==n2)
        return;

    if (n1->size > n2->size) {
        auto temp = n1;
        n1 = n2;
        n2 = temp;
    }
    n1->pointer = n2;
    n2->size += n1->size;

}

void disjoint_set::merge(int v1, int v2) {
    merge(&node_array[v1],&node_array[v2]);

}

void disjoint_set::print() {
    for (auto n: node_array) {
        cout<<n.second.value<<", "<<  find(&n.second)->value<<"\n";
    }
}

size_t disjoint_set::size() {
    return node_array.size();
}

void disjoint_set::reset() {
    for (auto &it: node_array) {
        it.second.size = 1;
        it.second.pointer = nullptr;
    }
}