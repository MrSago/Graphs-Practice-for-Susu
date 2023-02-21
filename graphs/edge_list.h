
#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include <fstream>
#include <map>

#include "adj_list.h"
#include "adj_matrix.h"
#include "graph_representation.h"

class AdjacencyMatrix;
class AdjacencyList;

class EdgeList : public GraphRepresentation {
   public:
    EdgeList() = default;
    EdgeList(const std::map<std::pair<int, int>, int>&& edges,
             const bool directed, const bool weighted,
             const int vertices_count);

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
    AdjacencyList* getNewAdjList();

    std::map<std::pair<int, int>, int>* getGraphPointer();

   private:
    // map: key - pair of vertices, value - weight
    std::map<std::pair<int, int>, int> edges_;
    int vertices_count_ = 0;
    bool directed_ = false;
    bool weighted_ = false;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // EDGE_LIST_H
