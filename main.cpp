/*
Условие:
Дан базовый интерфейс для представления ориентированного графа:
struct IGraph {
virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }
    
    return sorted;
}

void testGraph(const IGraph &graph, const std::function<void(int)> &func) {
    std::cout << "BFS: ";
    mainBFS(graph, func);
    std::cout << std::endl;

    std::cout << "DFS: ";
    mainDFS(graph, func);
    std::cout << std::endl;

    std::cout << "Topological Sort: ";
    for (int vertex: topologicalSort(graph)) {
        func(vertex);
    }
    std::cout << std::endl;
}

void test(){
    std::cout << "\tTesting Graphs:" << std::endl << std::endl;
    ListGraph listGraph(7);
    listGraph.AddEdge(0, 2);
    listGraph.AddEdge(0, 4);
    listGraph.AddEdge(1, 0);
    listGraph.AddEdge(1, 3);  
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(2, 1);
    listGraph.AddEdge(3, 0);
    listGraph.AddEdge(3, 5);
    listGraph.AddEdge(4, 3);
    listGraph.AddEdge(5, 2);
    listGraph.AddEdge(6, 1);
    listGraph.AddEdge(6, 5);

    MatrixGraph matrixGraph(listGraph);
    ArcGraph arcGraph(matrixGraph);
    SetGraph setGraph(arcGraph);

    std::cout << "-> ListGraph:" << std::endl;
    testGraph(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "-> MatrixGraph:" << std::endl;
    testGraph(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "-> ArcGraph:" << std::endl;
    testGraph(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    
    std::cout << "-> SetGraph:" << std::endl;
    testGraph(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
    test();
    return 0;
}