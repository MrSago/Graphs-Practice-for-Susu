
#ifndef ADJ_LIST_HPP
#define ADJ_LIST_HPP

#include <fstream>
#include <map>

#include "graph_representation.hpp"

class AdjacencyList : public GraphRepresentation {
   public:
    void readGraph(std::ifstream& file) override;
    void writeGraph(std::ofstream& file) override;
    void addEdge(const int from, const int to, const int weight = 0) override;
    void removeEdge(const int from, const int to) override;
    void changeEdge(const int from, const int to, const int weight) override;
    void printGraph() const override;
    void clearGraph() override;

   private:
    // map: key - pair of vertices, value - weight
    std::map<std::pair<int, int>, int> adjacencyList;
    int verticesCount = 0;
    bool isDirected = false;
    bool isWeighted = false;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_LIST_HPP
