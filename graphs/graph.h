
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
    Graph(GraphRepresentation* graph, GraphType graph_type);
    ~Graph();

    void readGraph(const std::string& filename);
    void writeGraph(const std::string& filename);
    void addEdge(const int from, const int to, const int weight = 1);
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
    GraphRepresentation* graph_repr_;
    GraphType graph_type_ = GraphType::Unknown;

    Prim prim;
    Kruscal kruscal;

    GraphRepresentation* allocNewGraph();
    AdjacencyMatrix* convertToNewAdjMatrix();
    AdjacencyList* convertToNewAdjList();
    EdgeList* convertToNewEdgeList();
};

#endif  // GRAPH_H