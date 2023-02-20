
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "edge_list.hpp"
#include "graph_representation.hpp"
#include "kruscal.hpp"
#include "prim.hpp"

enum class GraphType : char {
    AdjacencyMatrix = 'C',
    AdjacencyList = 'L',
    EdgeList = 'E',
    Unknown = 'U'
};

class Graph {
   public:
    Graph() = default;
    Graph(GraphRepresentation* graph, GraphType gtype);
    ~Graph();

    void readGraph(const std::string& fileName);
    void writeGraph(const std::string& fileName);
    void addEdge(const int from, const int to, const int weight);
    void removeEdge(const int from, const int to);
    void changeEdge(const int from, const int to, const int weight);

    void printGraph();
    void clearGraph();

    void transformToAdjMatrix();
    void transformToAdjList();
    void transformToListOfEdges();

    Graph getSpaingTreePrim();
    Graph getSpaingTreeKruscal();

   private:
    GraphRepresentation* graphRepr;
    GraphType graphType = GraphType::Unknown;

    Prim prim;
    Kruscal kruscal;

    GraphRepresentation* allocNewGraph();
    AdjacencyMatrix* convertToAdjMatrix();
    AdjacencyList* convertToAdjList();
    EdgeList* convertToEdgeList();
};

#endif  // GRAPH_HPP
