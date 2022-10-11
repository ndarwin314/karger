//
// Created by Noah Feinberg on 10/11/2022.
//

#ifndef KARGER_DISJOINT_SET_H
#define KARGER_DISJOINT_SET_H
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> Edge;

struct node{
    node *pointer;
    int size;
    Edge value;
};

class disjoint_set {

    public:
        vector<node> node_array;
        disjoint_set() = default;
        void add_node(Edge);
        node* find(node*);
        void merge(node*, node*);
        void print();
};


#endif //KARGER_DISJOINT_SET_H
