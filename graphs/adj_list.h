
#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <fstream>
#include <vector>

#include "adj_matrix.h"
#include "edge_list.h"
#include "graph_representation.h"

class AdjacencyMatrix;
class EdgeList;

class AdjacencyList : public GraphRepresentation {
   public:
    AdjacencyList() = default;
    AdjacencyList(const std::vector<std::vector<std::pair<int, int>>>&& list,
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

    AdjacencyMatrix* getNewAdjMatrix();
    EdgeList* getNewListOfEdges();

    std::vector<std::vector<std::pair<int, int>>>* getGraphPointer();

   private:
    // list_[from][i] = {to, weight};
    std::vector<std::vector<std::pair<int, int>>> list_;
    bool directed_ = false;
    bool weighted_ = false;
    int edges_count_ = 0;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_LIST_H
