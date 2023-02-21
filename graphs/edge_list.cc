
#include "edge_list.h"

#include <fstream>
#include <iostream>
#include <map>

#include "adj_list.h"
#include "adj_matrix.h"
#include "graph_representation.h"

EdgeList::EdgeList(const std::map<std::pair<int, int>, int>&& edges,
                   const bool directed, const bool weighted,
                   const int vertices_count)
    : edges_(edges),
      directed_(directed),
      weighted_(weighted),
      vertices_count_(vertices_count) {}

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
            edges_[{from - 1, to - 1}] = weight;
            if (!directed_) {
                edges_[{to - 1, from - 1}] = weight;
            }
        }
    } else {
        while (edge_count--) {
            int from, to;
            file >> from >> to;
            edges_[{from - 1, to - 1}] = 1;
            if (!directed_) {
                edges_[{to - 1, from - 1}] = 1;
            }
        }
    }
}

void EdgeList::writeGraph(std::ofstream& file) {
    std::map<std::pair<int, int>, bool> used;

    file << vertices_count_ << ' '
         << (directed_ ? edges_.size() : edges_.size() / 2) << '\n';
    file << directed_ << ' ' << weighted_ << '\n';

    if (weighted_) {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                file << edge.first + 1 << ' ' << edge.second + 1 << ' '
                     << weight << '\n';
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                file << edge.first + 1 << ' ' << edge.second + 1 << '\n';
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
            }
        }
    }
}

void EdgeList::addEdge(const int from, const int to, const int weight) {
    if (isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = weight;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::removeEdge(const int from, const int to) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = 0;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = 0;
    }
}

void EdgeList::changeEdge(const int from, const int to, const int weight) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    edges_[{from_idx, to_idx}] = weight;
    if (!directed_) {
        edges_[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::printGraph() const {
    std::map<std::pair<int, int>, bool> used;
    std::cout << "Edges list:\n";
    if (weighted_) {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << " (w: " << weight << ")\n";
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges_) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << '\n';
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
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

AdjacencyMatrix* EdgeList::getNewAdjMatrix() {
    std::vector<std::vector<int>> matrix(vertices_count_,
                                         std::vector<int>(vertices_count_, 0));
    for (const auto& [edge, weight] : edges_) {
        matrix[edge.first][edge.second] = weight;
    }
    return new AdjacencyMatrix(std::move(matrix), directed_, weighted_);
}

AdjacencyList* EdgeList::getNewAdjList() {
    std::vector<std::vector<std::pair<int, int>>> list(vertices_count_);
    for (const auto& [edge, weight] : edges_) {
        list[edge.first].push_back({edge.second, weight});
    }
    return new AdjacencyList(std::move(list), directed_, weighted_);
}

std::map<std::pair<int, int>, int>* EdgeList::getGraphPointer() {
    return &edges_;
}

bool EdgeList::isVerticeExist(const int vertice) const {
    return vertice > 0 && vertice <= vertices_count_;
}

bool EdgeList::isEdgeExist(const int from, const int to) const {
    return isVerticeExist(from) && isVerticeExist(to) &&
           edges_.at({from - 1, to - 1});
}
