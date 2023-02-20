
#include "graph.hpp"

#include <fstream>
#include <iostream>

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "edge_list.hpp"
#include "graph_representation.hpp"
#include "kruscal.hpp"
#include "prim.hpp"

Graph::Graph(GraphRepresentation* graph, GraphType gtype)
    : graphRepr(graph), graphType(gtype) {}

Graph::~Graph() { clearGraph(); }

void Graph::readGraph(const std::string& fileName) {
    std::ifstream file(fileName);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << fileName << '\n';
        return;
    }

    clearGraph();

    char gtype;
    file >> gtype;
    graphType = static_cast<GraphType>(gtype);
    graphRepr = allocNewGraph();

    graphRepr->readGraph(file);
}

void Graph::writeGraph(const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << fileName << '\n';
        return;
    }

    file << static_cast<char>(graphType) << ' ';

    graphRepr->writeGraph(file);
}

void Graph::addEdge(const int from, const int to, const int weight) {
    graphRepr->addEdge(from, to, weight);
}

void Graph::removeEdge(const int from, const int to) {
    graphRepr->removeEdge(from, to);
}

void Graph::changeEdge(const int from, const int to, const int weight) {
    graphRepr->changeEdge(from, to, weight);
}

void Graph::printGraph() { graphRepr->printGraph(); }

void Graph::clearGraph() {
    if (graphType != GraphType::Unknown) {
        graphRepr->clearGraph();
        delete graphRepr;
        graphType = GraphType::Unknown;
    }
}

void Graph::transformToAdjMatrix() {
    GraphRepresentation* newGraphRepr = convertToAdjMatrix();
    if (!newGraphRepr) {
        return;
    }
    clearGraph();
    graphRepr = newGraphRepr;
    graphType = GraphType::AdjacencyMatrix;
}

void Graph::transformToAdjList() {
    GraphRepresentation* newGraphRepr = convertToAdjList();
    if (!newGraphRepr) {
        return;
    }
    clearGraph();
    graphRepr = newGraphRepr;
    graphType = GraphType::AdjacencyList;
}

void Graph::transformToListOfEdges() {
    GraphRepresentation* newGraphRepr = convertToEdgeList();
    if (!newGraphRepr) {
        return;
    }
    clearGraph();
    graphRepr = newGraphRepr;
    graphType = GraphType::EdgeList;
}

Graph Graph::getSpaingTreePrim() {
    if (graphRepr->getEdgesCount() == graphRepr->getVerticesCount()) {
        AdjacencyMatrix* adjMatrix = convertToAdjMatrix();
        if (adjMatrix) {
            EdgeList* result = prim.getSpaingTreeDenseGraph(adjMatrix);
            adjMatrix->clearGraph();
            delete adjMatrix;
            return Graph(result, GraphType::EdgeList);
        }
        EdgeList* result = prim.getSpaingTreeDenseGraph(
            static_cast<AdjacencyMatrix*>(graphRepr));
        return Graph(result, GraphType::EdgeList);
    }

    AdjacencyList* adjList = convertToAdjList();
    if (adjList) {
        EdgeList* result = prim.getSpaingTreeSparseGraph(adjList);
        adjList->clearGraph();
        delete adjList;
        return Graph(result, GraphType::EdgeList);
    }
    EdgeList* result =
        prim.getSpaingTreeSparseGraph(static_cast<AdjacencyList*>(graphRepr));
    return Graph(result, GraphType::EdgeList);
}

Graph Graph::getSpaingTreeKruscal() {
    EdgeList* edgeList = convertToEdgeList();
    if (edgeList) {
        EdgeList* result = kruscal.getSpaingTree(edgeList);
        edgeList->clearGraph();
        delete edgeList;
        return Graph(result, GraphType::EdgeList);
    }
    EdgeList* result = kruscal.getSpaingTree(static_cast<EdgeList*>(graphRepr));
    return Graph(result, GraphType::EdgeList);
}

GraphRepresentation* Graph::allocNewGraph() {
    switch (graphType) {
        case GraphType::AdjacencyList:
            return new AdjacencyList();

        case GraphType::AdjacencyMatrix:
            return new AdjacencyMatrix();

        case GraphType::EdgeList:
            return new EdgeList();

        case GraphType::Unknown:
        default:
            return nullptr;
    }
}

AdjacencyMatrix* Graph::convertToAdjMatrix() {
    switch (graphType) {
        case GraphType::AdjacencyList:
            return static_cast<AdjacencyList*>(graphRepr)->getNewAdjMatrix();

        case GraphType::EdgeList:
            return static_cast<EdgeList*>(graphRepr)->getNewAdjMatrix();

        case GraphType::AdjacencyMatrix:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}

AdjacencyList* Graph::convertToAdjList() {
    switch (graphType) {
        case GraphType::AdjacencyMatrix:
            return static_cast<AdjacencyMatrix*>(graphRepr)->getNewAdjList();

        case GraphType::EdgeList:
            return static_cast<EdgeList*>(graphRepr)->getNewAdjList();

        case GraphType::AdjacencyList:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}

EdgeList* Graph::convertToEdgeList() {
    switch (graphType) {
        case GraphType::AdjacencyList:
            return static_cast<AdjacencyList*>(graphRepr)->getNewListOfEdges();

        case GraphType::AdjacencyMatrix:
            return static_cast<AdjacencyMatrix*>(graphRepr)
                ->getNewListOfEdges();

        case GraphType::EdgeList:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}
