
#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <fstream>
#include <vector>

#include "adj_matrix.h"
#include "edge_list.h"
#include "graph_representation.h"

class AdjacencyMatrix;
class EdgeList;

// list[from][i] = {to, weight};
using adj_list_t = std::vector<std::vector<std::pair<int, int>>>;

class AdjacencyList : public GraphRepresentation {
   public:
    AdjacencyList() = default;
    AdjacencyList(const int vertices_count, const bool directed,
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

    adj_list_t* getStructPointer();
    AdjacencyMatrix* getNewAdjMatrix();
    EdgeList* getNewListOfEdges();

   private:
    adj_list_t list_;
    int edges_count_;
    bool directed_;
    bool weighted_;
};

#endif  // ADJ_LIST_H
