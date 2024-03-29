
#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <fstream>
#include <vector>

#include "adj_list.h"
#include "edge_list.h"
#include "graph_representation.h"

class AdjacencyList;
class EdgeList;

using adj_matrix_t = std::vector<std::vector<int>>;

class AdjacencyMatrix : public GraphRepresentation {
   public:
    AdjacencyMatrix() = default;
    AdjacencyMatrix(const int vertices_count, const bool directed,
                    const bool weighted);

    void readGraph(std::ifstream& file) override;
    void writeGraph(std::ofstream& file) override;
    void addEdge(const int from, const int to, const int weight = 1) override;
    void removeEdge(const int from, const int to) override;
    void changeEdge(const int from, const int to, const int weight) override;

    void printGraph() const override;
    void clearGraph() override;
    int getVerticesCount() override;
    int getEdgesCount() override;

    adj_matrix_t* getStructPointer();
    AdjacencyList* getNewAdjList();
    EdgeList* getNewListOfEdges();

   private:
    adj_matrix_t matrix_;
    int edges_count_;
    bool directed_;
    bool weighted_;
};

#endif  // ADJ_MATRIX_H
