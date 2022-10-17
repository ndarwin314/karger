//
// Created by Noah Feinberg on 10/11/22.
//
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <unordered_set>
#include <utility>

#include "edge_list_graph.h"

edge_list_graph::edge_list_graph(disjoint_set set, vector<Edge> list) {
    edge_list = std::move(list);
    vertex_set = std::move(set);
    index = 0;
    size = vertex_set.size();
}

int edge_list_graph::bad(int vertex, unordered_set<int> set) {
    auto representative = vertex_set.find(vertex);
    if (set.find(representative) != set.end()) {
        return 1;
    }
    return -1;
}

vector<int> edge_list_graph::karger() {
    // TODO: move this somewhere else
    index = 0;
    vertex_set.reset();
    unsigned int time = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine {time};
    std::shuffle(std::begin(edge_list), std::end(edge_list), rng);
    int vertex_count = size;
    while (vertex_count > 4) {
        Edge edge = edge_list[index];
        if (vertex_set.find(edge.first) != vertex_set.find(edge.second)) {
            vertex_set.merge(edge.first, edge.second);
            vertex_count--;
        }
        index++;
    }

    vector<int> all;
    for (node n: vertex_set.node_array) {
        auto representative = vertex_set.find(n);
        if (std::find(all.begin(), all.end(), representative)==all.end()) {
            all.push_back(representative);
            if (all.size() == 4)
                break;
        }
    }
    //unordered_set<int> cut;
    unordered_set<int> complement;
    vector<int> out(7);
    for (int r=1; r<8; r++) {
        //cut.clear();
        complement.clear();
        //cut.insert(all[0]);
        for (int i=1; i<4; i++) {
            if ((r>>(i-1))&1) {
                complement.insert(all[i]);
            }
        }
        int cut_size = 0;
        for (int i=index; i<edge_list.size(); i++) {
            Edge edge = edge_list[i];
            if (bad(edge.first, complement)*bad(edge.second, complement)==-1) {
                cut_size += 1;
            }
        }
        out[r-1] = cut_size;
    }
    return out;
}