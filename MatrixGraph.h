#include "IGraph.h"
#include <vector>
#include <cassert>

struct MatrixGraph : public IGraph {
public:
    MatrixGraph(int size);
    MatrixGraph(const IGraph &graph);
    ~MatrixGraph() override;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> matrix;
};
