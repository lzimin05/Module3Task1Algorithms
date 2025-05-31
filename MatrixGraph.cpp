#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size): matrix(size, std::vector<int>(size, 0)){}

MatrixGraph::MatrixGraph(const IGraph &graph){
    matrix.resize(graph.VerticesCount(), std::vector<int>(graph.VerticesCount(), 0));
    for (int i = 0; i < graph.VerticesCount(); i++){
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int v: vertices){
            matrix[i][v] = 1;
        }
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to){
    assert(0 <= from && from < matrix.size());
    assert(0 <= to && to < matrix.size());
    matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const{
    return matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const{
    assert(0 <= vertex && vertex < matrix.size());
    std::vector<int> nextVertices;
    for (int to = 0; to < matrix.size(); to++){
        if (matrix[vertex][to] != 0){
            nextVertices.push_back(to);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const{
    assert(0 <= vertex && vertex < matrix.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < matrix.size(); from++){
        if (matrix[from][vertex] != 0){
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
