
#ifndef GRAPH_H
#define GRAPH_H

#include "adj_list.h"
#include "adj_matrix.h"
#include "edge_list.h"
#include "graph_representation.h"
#include "kruscal.h"
#include "prim.h"

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

#endif  // GRAPH_H
