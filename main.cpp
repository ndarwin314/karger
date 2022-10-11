#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <algorithm>

#include "disjoint_set.h"

using namespace std;

vector<int> karger(disjoint_set set, int vertex_count) {
    vector<node> out;
    while (vertex_count >= 4) {
        vertex_count--;
        std::sample(
                set.node_array.begin(),
                set.node_array.end(),
                std::back_inserter(out),
                1,
                std::mt19937{std::random_device{}()}
        );
    }
}

int main() {
    string file_name = R"(C:\Users\Noah Feinberg\CLionProjects\karger\karger1.txt)";
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "balls";
        return -1;
    }
    disjoint_set set;
    std::unordered_set<int> vertices;
    string line;
    while ( getline (file,line) ) {
        int split_index = line.find(' ');
        int start = stoi(line.substr(0, split_index));
        int end = stoi(line.substr(split_index+1, line.size()));
        set.add_node(Edge{start, end});
        vertices.insert(start);
        vertices.insert(end);
    }
    file.close();
    karger(set, vertices.size());
    return 0;
}
