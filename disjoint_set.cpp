//
// Created by Noah Feinberg on 10/11/2022.
//

#include "disjoint_set.h"
#include <iostream>

void disjoint_set::add_node(Edge edge) {
    node n{nullptr, 1, edge};
    node_array.push_back(n);
    for (auto m: node_array) {
        if (m.value.second == n.value.second) {
            merge(&m, &n);
            return;
        }
    }
}

node* disjoint_set::find(node* n) {
    if (n->pointer != nullptr) {
        n->pointer = find(n->pointer);
        return n->pointer;
    } else {
        return n;
    }
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

void disjoint_set::print() {
    for (auto n: node_array) {
        cout<<n.value.first<<", "<<n.value.second<<"\n";
    }
}