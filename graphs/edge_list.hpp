
#ifndef EDGE_LIST_HPP
#define EDGE_LIST_HPP

#include <fstream>
#include <map>

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "graph_representation.hpp"

class AdjacencyMatrix;
class AdjacencyList;

class EdgeList : public GraphRepresentation {
   public:
    EdgeList() = default;
    EdgeList(const std::map<std::pair<int, int>, int>&& edges,
             const bool isDirected, const bool isWeighted,
             const int verticesCount);

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
    std::map<std::pair<int, int>, int> edges;
    int verticesCount = 0;
    bool isDirected = false;
    bool isWeighted = false;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // EDGE_LIST_HPP
