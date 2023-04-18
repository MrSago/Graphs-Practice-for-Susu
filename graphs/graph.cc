
#include "graph.h"

#include <fstream>
#include <iostream>

#include "adj_list.h"
#include "adj_matrix.h"
#include "edge_list.h"
#include "graph_representation.h"
#include "kruscal.h"
#include "prim.h"

Graph::Graph() = default;

Graph::Graph(GraphRepresentation* graph, GraphType graph_type)
    : graph_repr_(graph), graph_type_(graph_type) {}

Graph::~Graph() { clearGraph(); }

void Graph::readGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    clearGraph();

    char graph_type;
    file >> graph_type;
    graph_type_ = static_cast<GraphType>(graph_type);
    graph_repr_ = allocNewGraph();

    graph_repr_->readGraph(file);
}

void Graph::writeGraph(const std::string& filename) {
    std::ofstream file(filename);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    file << static_cast<char>(graph_type_) << ' ';

    graph_repr_->writeGraph(file);
}

void Graph::addEdge(const int from, const int to, const int weight) {
    graph_repr_->addEdge(from, to, weight);
}

void Graph::removeEdge(const int from, const int to) {
    graph_repr_->removeEdge(from, to);
}

void Graph::changeEdge(const int from, const int to, const int weight) {
    graph_repr_->changeEdge(from, to, weight);
}

void Graph::printGraph() { graph_repr_->printGraph(); }

void Graph::clearGraph() {
    if (graph_type_ != GraphType::Unknown) {
        graph_repr_->clearGraph();
        delete graph_repr_;
        graph_type_ = GraphType::Unknown;
    }
}

void Graph::transformToAdjMatrix() {
    GraphRepresentation* new_graph = convertToNewAdjMatrix();
    if (!new_graph) {
        return;
    }
    clearGraph();
    graph_repr_ = new_graph;
    graph_type_ = GraphType::AdjacencyMatrix;
}

void Graph::transformToAdjList() {
    GraphRepresentation* new_graph = convertToNewAdjList();
    if (!new_graph) {
        return;
    }
    clearGraph();
    graph_repr_ = new_graph;
    graph_type_ = GraphType::AdjacencyList;
}

void Graph::transformToListOfEdges() {
    GraphRepresentation* new_graph = convertToNewEdgeList();
    if (!new_graph) {
        return;
    }
    clearGraph();
    graph_repr_ = new_graph;
    graph_type_ = GraphType::EdgeList;
}

Graph Graph::getSpaingTreeBoruvka() {
    EdgeList* edge_list = convertToNewEdgeList();
    if (edge_list) {
        EdgeList* result = boruvki_.getSpaingTree(*edge_list);
        edge_list->clearGraph();
        delete edge_list;
        return Graph(result, GraphType::EdgeList);
    }

    EdgeList* result =
        boruvki_.getSpaingTree((*static_cast<EdgeList*>(graph_repr_)));
    return Graph(result, GraphType::EdgeList);
}

Graph Graph::getSpaingTreePrim() {
    if (graph_repr_->getEdgesCount() == graph_repr_->getVerticesCount()) {
        AdjacencyMatrix* adj_matrix = convertToNewAdjMatrix();
        if (adj_matrix) {
            EdgeList* result = prim_.getSpaingTreeDenseGraph(*adj_matrix);
            adj_matrix->clearGraph();
            delete adj_matrix;
            return Graph(result, GraphType::EdgeList);
        }
        EdgeList* result = prim_.getSpaingTreeDenseGraph(
            *(static_cast<AdjacencyMatrix*>(graph_repr_)));
        return Graph(result, GraphType::EdgeList);
    }

    AdjacencyList* adj_list = convertToNewAdjList();
    if (adj_list) {
        EdgeList* result = prim_.getSpaingTreeSparseGraph(*adj_list);
        adj_list->clearGraph();
        delete adj_list;
        return Graph(result, GraphType::EdgeList);
    }
    EdgeList* result = prim_.getSpaingTreeSparseGraph(
        (*static_cast<AdjacencyList*>(graph_repr_)));
    return Graph(result, GraphType::EdgeList);
}

Graph Graph::getSpaingTreeKruscal() {
    EdgeList* edge_list = convertToNewEdgeList();
    if (edge_list) {
        EdgeList* result = kruscal_.getSpaingTree(*edge_list);
        edge_list->clearGraph();
        delete edge_list;
        return Graph(result, GraphType::EdgeList);
    }
    EdgeList* result =
        kruscal_.getSpaingTree((*static_cast<EdgeList*>(graph_repr_)));
    return Graph(result, GraphType::EdgeList);
}

GraphRepresentation* Graph::allocNewGraph() {
    switch (graph_type_) {
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

AdjacencyMatrix* Graph::convertToNewAdjMatrix() {
    switch (graph_type_) {
        case GraphType::AdjacencyList:
            return static_cast<AdjacencyList*>(graph_repr_)->getNewAdjMatrix();

        case GraphType::EdgeList:
            return static_cast<EdgeList*>(graph_repr_)->getNewAdjMatrix();

        case GraphType::AdjacencyMatrix:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}

AdjacencyList* Graph::convertToNewAdjList() {
    switch (graph_type_) {
        case GraphType::AdjacencyMatrix:
            return static_cast<AdjacencyMatrix*>(graph_repr_)->getNewAdjList();

        case GraphType::EdgeList:
            return static_cast<EdgeList*>(graph_repr_)->getNewAdjList();

        case GraphType::AdjacencyList:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}

EdgeList* Graph::convertToNewEdgeList() {
    switch (graph_type_) {
        case GraphType::AdjacencyList:
            return static_cast<AdjacencyList*>(graph_repr_)
                ->getNewListOfEdges();

        case GraphType::AdjacencyMatrix:
            return static_cast<AdjacencyMatrix*>(graph_repr_)
                ->getNewListOfEdges();

        case GraphType::EdgeList:
        case GraphType::Unknown:
        default:
            return nullptr;
    }
    return nullptr;
}
