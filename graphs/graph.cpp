
#include "graph.hpp"

#include <fstream>
#include <iostream>

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
    allocNewGraph();

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
    GraphRepresentation* newGraphRepr;
    switch (graphType) {
        case GraphType::AdjacencyList:
            newGraphRepr =
                static_cast<AdjacencyList*>(graphRepr)->getAdjMatrix();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::AdjacencyMatrix;
            break;

        case GraphType::EdgeList:
            newGraphRepr = static_cast<EdgeList*>(graphRepr)->getAdjMatrix();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::AdjacencyMatrix;
            break;

        case GraphType::AdjacencyMatrix:
        case GraphType::Unknown:
        default:
            break;
    }
}

void Graph::transformToAdjList() {
    GraphRepresentation* newGraphRepr;
    switch (graphType) {
        case GraphType::AdjacencyMatrix:
            newGraphRepr =
                static_cast<AdjacencyMatrix*>(graphRepr)->getAdjList();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::AdjacencyList;
            break;

        case GraphType::EdgeList:
            newGraphRepr = static_cast<EdgeList*>(graphRepr)->getAdjList();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::AdjacencyList;
            break;

        case GraphType::AdjacencyList:
        case GraphType::Unknown:
        default:
            break;
    }
}

void Graph::transformToListOfEdges() {
    GraphRepresentation* newGraphRepr;
    switch (graphType) {
        case GraphType::AdjacencyList:
            newGraphRepr =
                static_cast<AdjacencyList*>(graphRepr)->getListOfEdges();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::EdgeList;
            break;

        case GraphType::AdjacencyMatrix:
            newGraphRepr =
                static_cast<AdjacencyMatrix*>(graphRepr)->getListOfEdges();
            clearGraph();
            graphRepr = newGraphRepr;
            graphType = GraphType::EdgeList;
            break;

        case GraphType::EdgeList:
        case GraphType::Unknown:
        default:
            break;
    }
}

void Graph::allocNewGraph() {
    switch (graphType) {
        case GraphType::AdjacencyList:
            graphRepr = new AdjacencyList();
            return;

        case GraphType::AdjacencyMatrix:
            graphRepr = new AdjacencyMatrix();
            return;

        case GraphType::EdgeList:
            graphRepr = new EdgeList();
            return;

        case GraphType::Unknown:
        default:
            return;
    }
}
