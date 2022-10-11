#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <random>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/random.hpp>

using namespace std;
using namespace boost;

typedef pair<string, string> Edge;
typedef adjacency_list<vecS, listS, undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

template<class edge_descriptor>
struct edge_target_predicate {
    Vertex v;

    bool operator()(const edge_descriptor& e) const {
        return e.m_source == v || e.m_target == v;
    }
};

void print_graph(Graph const& g)
{
    auto vs = boost::vertices(g);
    for (auto vit = vs.first; vit != vs.second; ++vit) {
        auto neighbors = boost::adjacent_vertices(*vit, g);
        for (auto nit = neighbors.first; nit != neighbors.second; ++nit)
            std::cout << "{" << *vit << "," << *nit << "}" << ", ";
    }
    std::cout << "\n";
}

void contract_vertices(Graph::edge_descriptor e, Graph& g)
{
    auto b = e.m_target;
    auto a = e.m_source;
    auto be = boost::adjacent_vertices(b, g);
    for (auto beit = be.first; beit != be.second; ++beit) {
        add_edge(a, *beit, g);
    }
    edge_target_predicate<Graph::edge_descriptor> p{b};
    remove_edge_if(p, g);
    remove_vertex(b, g);
}

void karger(Graph g, int output[7], default_random_engine rng) {
    int vertex_count = g.vertex_set().size();
    while (vertex_count >= 4) {
        //uniform_int_distribution<int> dis(0, edge_count-1);
        Graph::edge_descriptor e = random_edge(g, rng);
        contract_vertices(e, g);
        vertex_count--;
    }
    print_graph(g);
    output[0] = 1;
}

int main1() {
    string file_name = R"(C:\Users\Noah Feinberg\CLionProjects\karger\karger1.txt)";
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "balls";
        return -1;
    }
    string line;
    std::unordered_map<string, boost::graph_traits<Graph>::vertex_descriptor> vertices;
    Graph g;
    while(getline(file, line)) {
        int split_index = line.find(' ');
        string start = line.substr(0, split_index);
        string end = line.substr(split_index+1, line.size());
        if (vertices.find(start)==vertices.end())
            vertices[start] = add_vertex(g);

        if (vertices.find(end)==vertices.end())
            vertices[end] = add_vertex(g);

        if (start!=end)
            add_edge(vertices[start], vertices[end], g);
    }
    default_random_engine rng;
    int output[7];
    print_graph(g);
    karger(g, output, rng);

    return 0;
}
