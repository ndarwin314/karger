//
// Created by Noah Feinberg on 10/11/2022.
//

#include "disjoint_set.h"
#include <iostream>


void disjoint_set::add_node(int vertex) {
    node n{vertex, 1, vertex};
    node_array[vertex] = n;
}

disjoint_set::disjoint_set(int size) {
    node_array.resize(size);
}


int disjoint_set::find(node n) {
    if (n.pointer != n.value) {
        n.pointer = find(node_array[n.pointer]);
        return n.pointer;
    } else {
        return n.value;
    }
}

int disjoint_set::find(int vertex) {
    return find(node_array[vertex]);
}

void disjoint_set::merge(node n1, node n2) {
    n1 = node_array[find(n1)];
    n2 = node_array[find(n2)];
    if (n1.value==n2.value)
        return;

    if (n1.size > n2.size) {
        auto temp = n1;
        n1 = n2;
        n2 = temp;
    }
    n1.pointer = n2.value;
    n2.size += n1.size;

}

void disjoint_set::merge(int v1, int v2) {
    merge(node_array[v1],node_array[v2]);

}

void disjoint_set::print() {
    for (auto n: node_array) {
        cout<<n.value<<", "<<  node_array[find(n)].value<<"\n";
    }
}

size_t disjoint_set::size() {
    return node_array.size();
}

void disjoint_set::reset() {
    for (int i=0; i < node_array.size(); i++) {
        node_array[i].size = 1;
        node_array[i].value = i;
    }
}