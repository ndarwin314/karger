//
// Created by Noah Feinberg on 10/11/2022.
//

#ifndef KARGER_DISJOINT_SET_H
#define KARGER_DISJOINT_SET_H
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

typedef pair<int, int> Edge;

struct node{
    node *pointer;
    int size;
    int value;
};

class disjoint_set {

public:
    unordered_map<int, node> node_array;
    disjoint_set() = default;
    void add_node(int);
    node* find(node*);
    node* find(int);
    void merge(node*, node*);
    void merge(int, int);
    size_t size();
    void print();
};


#endif //KARGER_DISJOINT_SET_H
