
#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <fstream>
#include <vector>

#include "adj_list.h"
#include "edge_list.h"
#include "graph_representation.h"

class AdjacencyList;
class EdgeList;

class AdjacencyMatrix : public GraphRepresentation {
   public:
    AdjacencyMatrix() = default;
    AdjacencyMatrix(const std::vector<std::vector<int>>&& matrix,
                    const bool directed, const bool weighted);

    void readGraph(std::ifstream& file) override;
    void writeGraph(std::ofstream& file) override;
    void addEdge(const int from, const int to, const int weight = 0) override;
    void removeEdge(const int from, const int to) override;
    void changeEdge(const int from, const int to, const int weight) override;

    void printGraph() const override;
    void clearGraph() override;
    int getVerticesCount() override;
    int getEdgesCount() override;

    AdjacencyList* getNewAdjList();
    EdgeList* getNewListOfEdges();

    std::vector<std::vector<int>>* getGraphPointer();

   private:
    std::vector<std::vector<int>> matrix_;
    bool directed_ = false;
    bool weighted_ = false;
    int edges_count_ = 0;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_MATRIX_H
