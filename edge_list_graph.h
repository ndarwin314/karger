//
// Created by Noah Feinberg on 10/11/22.
//

#ifndef KARGER2_EDGE_LIST_GRAPH_H
#define KARGER2_EDGE_LIST_GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>

#include "boost/pending/disjoint_sets.hpp"

using namespace boost;
using namespace std;

typedef std::pair<int, int> Edge;
typedef disjoint_sets<unordered_map<int, int>, unordered_map<int, int>> union_find;

class edge_list_graph {
    std::default_random_engine rng;
public:
    disjoint_sets<union_find, union_find> vertex_set;
    vector<Edge> edge_list;
    int index, size;
    template<typename k>
    edge_list_graph(k, vector<Edge>);
    vector<int> karger();
    int bad(int, const unordered_set<int>&);
    void reset();
};


#endif //KARGER2_EDGE_LIST_GRAPH_H
