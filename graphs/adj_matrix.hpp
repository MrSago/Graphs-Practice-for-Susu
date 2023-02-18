
#ifndef ADJ_MATRIX_HPP
#define ADJ_MATRIX_HPP

#include <fstream>
#include <vector>

#include "adj_list.hpp"
#include "edge_list.hpp"
#include "graph_representation.hpp"

class AdjacencyList;
class EdgeList;

class AdjacencyMatrix : public GraphRepresentation {
   public:
    AdjacencyMatrix() = default;
    AdjacencyMatrix(const std::vector<std::vector<int>>&& matrix,
                    const bool isDirected, const bool isWeighted);

    void readGraph(std::ifstream& file) override;
    void writeGraph(std::ofstream& file) override;
    void addEdge(const int from, const int to, const int weight = 0) override;
    void removeEdge(const int from, const int to) override;
    void changeEdge(const int from, const int to, const int weight) override;

    void printGraph() const override;
    void clearGraph() override;

    AdjacencyList* getNewAdjList();
    EdgeList* getNewListOfEdges();

    std::vector<std::vector<int>>& getMatrix();

   private:
    std::vector<std::vector<int>> matrix;
    bool isDirected = false;
    bool isWeighted = false;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_MATRIX_HPP
