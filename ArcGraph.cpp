#include "ArcGraph.h"


Arc::Arc(int from, int to): from(from), to(to) {}

ArcGraph::ArcGraph(int size): vertices(size) {}

ArcGraph::ArcGraph(const IGraph &graph){
    vertices = graph.VerticesCount();
    for (int i = 0; i < graph.VerticesCount(); i++){
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int v: nextVertices){
            arc.push_back(Arc(i, v));
        }
    }
}

void ArcGraph::AddEdge(int from, int to){
    assert(0 <= from && from < vertices);
    assert(0 <= to && to < vertices);
    arc.push_back(Arc(from, to));
}

int ArcGraph::VerticesCount() const{
    return vertices;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const{
    assert(0 <= vertex && vertex < vertices);
    std::vector<int> nextVertices;
    for (Arc arc1: arc){
        if (arc1.from == vertex){
            nextVertices.push_back(arc1.to);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const{
    assert(0 <= vertex && vertex < vertices);
    std::vector<int> prevVertices;
    for (Arc arc: arc){
        if (arc.to == vertex){
            prevVertices.push_back(arc.from);
        }
    }
    return prevVertices;
}