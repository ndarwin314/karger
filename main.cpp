#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <algorithm>

#include "disjoint_set.h"
#include "edge_list_graph.h"

using namespace std;

typedef edge_list_graph Graph;

vector<int> karger(Graph g) {
    return g.karger();
}

int main() {
    string file_name = R"(../karger1.txt)";
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "balls";
        return -1;
    }
    disjoint_set set;
    vector<Edge> edge_list;
    unordered_set<int> vertices;
    string line;
    while ( getline (file,line) ) {
        int split_index = line.find(' ');
        int start = stoi(line.substr(0, split_index));
        int end = stoi(line.substr(split_index, line.size()));
        vertices.insert(start);
        vertices.insert(end);
        edge_list.emplace_back(start, end);
    }
    for (auto vertex: vertices) {
        set.add_node(vertex);
    }
    Graph graph(set, edge_list);
    vector<int> test(1000, 0);
    int bound = 1000;
    for (int i=0; i<bound; i++) {
        for (int size: karger(graph)) {
            test[size] += 1;
        }
    }
    for (int i=0; i<test.size(); i++) {
        int count = test[i];
        if (count != 0) {
            cout << "Mincut has size " << i << " with probability " << count / (7.0*bound);
            break;
        }
    }
    return 0;
}
