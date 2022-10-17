#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <chrono>

#include "disjoint_set.h"
#include "edge_list_graph.h"

using namespace std;

typedef edge_list_graph Graph;

vector<int> karger(Graph g) {
    return g.karger();
}

int main() {
    string file_name = R"(../karger3.txt)";
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "balls";
        return -1;
    }

    vector<Edge> edge_list;
    set<int> vertices;
    string line;
    while ( getline (file,line) ) {
        int split_index = line.find(' ');
        int start = stoi(line.substr(0, split_index));
        int end = stoi(line.substr(split_index, line.size()));
        if (start != end) {
            vertices.insert(start);
            vertices.insert(end);
            edge_list.emplace_back(start, end);
        }
    }
    disjoint_set set(*vertices.end());
    for (auto vertex: vertices) {
        set.add_node(vertex);
    }
    auto start = chrono::high_resolution_clock::now();
    Graph graph(set, edge_list);
    vector<int> test(1000, 0);
    int bound = 100;
    for (int i=0; i<bound; i++) {
        if (i%(bound/10)==0) {
            cout<<i<<"\n";
        }
        for (int size: graph.karger()) {
            test[size] += 1;
        }
    }
    for (int i=0; i<test.size(); i++) {
        int count = test[i];
        if (count != 0) {
            cout << "Mincut has size " << i << " with probability p=" << count / (7.0*bound)<<"\n";
            break;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
    cout<<duration.count()/1000.0;
    return 0;
}
