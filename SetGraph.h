#include "IGraph.h"
#include <vector>
#include <map>
#include <cassert>

class SetGraph : public IGraph {
public:
    explicit SetGraph(int size);
    explicit SetGraph(const IGraph& graph);
    ~SetGraph() override = default;
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::map<int, int>> hash;
};