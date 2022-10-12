//
// Created by Noah Feinberg on 10/11/22.
//
#include <random>
#include <algorithm>
#include <chrono>
#include <unordered_set>

#include "edge_list_graph.h"

edge_list_graph::edge_list_graph(disjoint_set set, vector<Edge> list) {
    edge_list = list;
    vertex_set = set;
    index = 0;
    size = vertex_set.size();
}

int edge_list_graph::bad(int vertex, unordered_set<int> set) {
    if (set.find(vertex_set.find(vertex)->value) != set.end()) {
        return 1;
    }
    return -1;
}

void edge_list_graph::karger(vector<int> out) {
    // TODO: move this somewhere else
    unsigned int time = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine {time};
    std::shuffle(std::begin(edge_list), std::end(edge_list), rng);
    for (;index<size-4; index++) {
        Edge edge = edge_list[index];
        vertex_set.merge(edge.first, edge.second);
    }
    unordered_set<int> cut;
    unordered_set<int> complement;
    int shift = 0;
    for (int r=1; r<8; r++) {
        cut.empty();
        complement.empty();
        auto it = vertex_set.node_array.begin();
        cut.insert(vertex_set.find(&it->second)->value);
        it++;
        while (it != vertex_set.node_array.end()) {
            if (cut.find(it->first)!=cut.end() || cut.find(it->first)!=cut.end()) {
                // extract digit
                int vertex = vertex_set.find(&it->second)->value;
                if ((r>>shift)&1) {
                    complement.insert(vertex);
                } else {
                    cut.insert(vertex);
                }
            }
        }
        int cut_size = 0;
        for (int i=index; i<edge_list.size(); i++) {
            Edge edge = edge_list[i];
            if (bad(edge.first, cut)*bad(edge.second, cut)==-1) {
                cut_size += 1;
            }
        }
        out[r-1] = cut_size;
    }

}