//
// Created by Noah Feinberg on 10/11/22.
//

#ifndef KARGER2_EDGE_LIST_GRAPH_H
#define KARGER2_EDGE_LIST_GRAPH_H

#include <vector>
#include <utility>

#include "disjoint_set.h"

typedef std::pair<int, int> Edge;

class edge_list_graph {

public:
    disjoint_set vertex_set;
    vector<Edge> edge_list;
    int index, size;
    edge_list_graph(disjoint_set, vector<Edge>);
    vector<int> karger();
    int bad(int, unordered_set<int>);
};


#endif //KARGER2_EDGE_LIST_GRAPH_H
