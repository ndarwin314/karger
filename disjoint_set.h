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
    int pointer;
    int size;
    int value;
};

class disjoint_set {

public:
    vector<node> node_array;
    disjoint_set() = default;
    disjoint_set(int);
    void add_node(int);
    int find(node);
    int find(int);
    void merge(node, node);
    void merge(int, int);
    size_t size();
    void reset();
    void print();
};


#endif //KARGER_DISJOINT_SET_H
