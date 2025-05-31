#include "SetGraph.h"

SetGraph::SetGraph(int size) : hash(size) {}

SetGraph::SetGraph(const IGraph& graph) {
    hash.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++) {
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int v : vertices) {
            hash[i][v] = 1;
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < hash.size());
    assert(0 <= to && to < hash.size());
    hash[from][to] = 1;
}

int SetGraph::VerticesCount() const {
    return hash.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < hash.size());
    std::vector<int> nextVertices;
    for (const auto& v : hash[vertex]) {
        nextVertices.push_back(v.first);
    }
    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < hash.size());
    std::vector<int> prevVertices;
    for (int from = 0; from < hash.size(); from++) {
        if (hash[from].find(vertex) != hash[from].end()) {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}