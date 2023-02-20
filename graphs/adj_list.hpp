
#ifndef ADJ_LIST_HPP
#define ADJ_LIST_HPP

#include <fstream>
#include <set>
#include <tuple>
#include <vector>

#include "adj_matrix.hpp"
#include "edge_list.hpp"
#include "graph_representation.hpp"

class AdjacencyMatrix;
class EdgeList;

class AdjacencyList : public GraphRepresentation {
   public:
    AdjacencyList() = default;
    AdjacencyList(const std::vector<std::vector<std::pair<int, int>>>&& list,
                  const bool isDirected, const bool isWeighted);

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
    // vector[from][i] = {to, weight};
    std::vector<std::vector<std::pair<int, int>>> list;
    bool isDirected = false;
    bool isWeighted = false;
    int edgesCount = 0;

    bool isVerticeExist(const int vertice) const;
    bool isEdgeExist(const int from, const int to) const;
};

#endif  // ADJ_LIST_HPP
