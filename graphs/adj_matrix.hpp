
#ifndef ADJ_MATRIX_HPP
#define ADJ_MATRIX_HPP

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "graph_representation.hpp"

class AdjacencyMatrix : public GraphRepresentation {
   public:
    void readGraph(std::ifstream& file) override;
    void writeGraph(std::ofstream& file) override;
    void addEdge(const int from, const int to, const int weight = 0) override;
    void removeEdge(const int from, const int to) override;
    void changeEdge(const int from, const int to, const int weight) override;
    void printGraph() const override;
    void clearGraph() override;

   private:
    std::vector<std::vector<int>> adjacencyMatrix;
    bool isDirected = false;
    bool isWeighted = false;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_MATRIX_HPP
