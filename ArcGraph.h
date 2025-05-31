#pragma once

#include "IGraph.h"
#include <vector>
#include <cassert>

struct Arc{
    Arc(int from, int to);
    int from, to;
};

struct ArcGraph : public IGraph {
public:
    ArcGraph(int size);
    ArcGraph(const IGraph &graph);
    ~ArcGraph() override = default;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<Arc> arc;
    int vertices;
};