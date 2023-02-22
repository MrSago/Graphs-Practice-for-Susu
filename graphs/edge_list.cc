
#include "edge_list.h"

#include <fstream>
#include <iostream>
#include <map>

#include "adj_list.h"
#include "adj_matrix.h"
#include "graph_representation.h"

EdgeList::EdgeList(const int vertices_count, const bool directed,
                   const bool weighted)
    : vertices_count_(vertices_count),
      directed_(directed),
      weighted_(weighted) {}

void EdgeList::readGraph(std::ifstream& file) {
    clearGraph();

    file >> vertices_count_;

    int edge_count;
    file >> edge_count;

    file >> directed_ >> weighted_;

    if (weighted_) {
        while (edge_count--) {
            int from, to, weight;
            file >> from >> to >> weight;
            addEdge(from, to, weight);
        }
    } else {
        while (edge_count--) {
            int from, to;
            file >> from >> to;
            addEdge(from, to);
        }
    }
}

void EdgeList::writeGraph(std::ofstream& file) {
    std::map<std::pair<int, int>, bool> used_edges;

    file << vertices_count_ << ' '
         << (directed_ ? edges_.size() : (edges_.size() >> 1)) << '\n';
    file << directed_ << ' ' << weighted_ << '\n';

    if (weighted_) {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used_edges[{edge.first, edge.second}] &&
                !used_edges[{edge.second, edge.first}]) {
                file << edge.first + 1 << ' ' << edge.second + 1 << ' '
                     << weight << '\n';
                used_edges[{edge.first, edge.second}] = true;
                used_edges[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used_edges[{edge.first, edge.second}] &&
                !used_edges[{edge.second, edge.first}]) {
                file << edge.first + 1 << ' ' << edge.second + 1 << '\n';
                used_edges[{edge.first, edge.second}] = true;
                used_edges[{edge.second, edge.first}] = true;
            }
        }
    }
}

void EdgeList::addEdge(const int from, const int to, const int weight) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = weight;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::removeEdge(const int from, const int to) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = 0;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = 0;
    }
}

void EdgeList::changeEdge(const int from, const int to, const int weight) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = weight;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::printGraph() const {
    std::map<std::pair<int, int>, bool> used_edges;
    std::cout << "Edges list:\n";
    if (weighted_) {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used_edges[{edge.first, edge.second}] &&
                !used_edges[{edge.second, edge.first}]) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << " (w: " << weight << ")\n";
                used_edges[{edge.first, edge.second}] = true;
                used_edges[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used_edges[{edge.first, edge.second}] &&
                !used_edges[{edge.second, edge.first}]) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << '\n';
                used_edges[{edge.first, edge.second}] = true;
                used_edges[{edge.second, edge.first}] = true;
            }
        }
    }
}

void EdgeList::clearGraph() {
    edges_.clear();
    vertices_count_ = 0;
    directed_ = weighted_ = false;
}

int EdgeList::getVerticesCount() { return vertices_count_; }

int EdgeList::getEdgesCount() { return edges_.size(); }

edge_list_t* EdgeList::getStructPointer() { return &edges_; }

AdjacencyMatrix* EdgeList::getNewAdjMatrix() {
    AdjacencyMatrix* adj_matrix =
        new AdjacencyMatrix(directed_, weighted_, vertices_count_);
    for (const auto& [edge, weight] : edges_) {
        adj_matrix->addEdge(edge.first + 1, edge.second + 1, weight);
    }
    return adj_matrix;
}

AdjacencyList* EdgeList::getNewAdjList() {
    AdjacencyList* adj_list =
        new AdjacencyList(directed_, weighted_, vertices_count_);
    for (const auto& [edge, weight] : edges_) {
        adj_list->addEdge(edge.first + 1, edge.second + 1, weight);
    }
    return adj_list;
}
