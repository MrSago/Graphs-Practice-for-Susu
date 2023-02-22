
#ifndef EDGE_LIST_H
#define EDGE_LIST_H

#include <fstream>
#include <map>

#include "adj_list.h"
#include "adj_matrix.h"
#include "graph_representation.h"

class AdjacencyMatrix;
class AdjacencyList;

// map: key - pair of vertices, value - weight
using edge_list_t = std::map<std::pair<int, int>, int>;

class EdgeList : public GraphRepresentation {
   public:
    EdgeList() = default;
    EdgeList(const int vertices_count, const bool directed,
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

    edge_list_t* getStructPointer();
    AdjacencyMatrix* getNewAdjMatrix();
    AdjacencyList* getNewAdjList();

   private:
    edge_list_t edges_;
    int vertices_count_;
    bool directed_;
    bool weighted_;
};

#endif  // EDGE_LIST_H
