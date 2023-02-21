
#include "adj_list.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "adj_matrix.h"
#include "edge_list.h"
#include "graph_representation.h"

AdjacencyList::AdjacencyList(
    const std::vector<std::vector<std::pair<int, int>>>&& list,
    const bool directed, const bool weighted)
    : list_(list), directed_(directed), weighted_(weighted) {}

void AdjacencyList::readGraph(std::ifstream& file) {
    clearGraph();

    int vertices_count;
    file >> vertices_count;
    list_.resize(vertices_count);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    file >> directed_ >> weighted_;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (weighted_) {
        int from_idx, to, weight;
        from_idx = to = weight = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            while (iss >> to >> weight) {
                list_[from_idx].push_back({to - 1, weight});
                // if (!directed_) {
                //     list_[to - 1].push_back({from_idx, weight});
                // }
                ++edges_count_;
            }
            ++from_idx;
        }
    } else {
        int from_idx, to;
        from_idx = to = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            while (iss >> to) {
                list_[from_idx].push_back({to - 1, 1});
                // if (!directed_) {
                //     list_[to - 1].push_back({from_idx, 1});
                // }
                ++edges_count_;
            }
            ++from_idx;
        }
    }
}

void AdjacencyList::writeGraph(std::ofstream& file) {
    std::map<std::pair<int, int>, bool> used;

    file << list_.size() << '\n';
    file << directed_ << ' ' << weighted_ << '\n';

    if (weighted_) {
        for (int i = 0; i < list_.size(); ++i) {
            for (const auto& edge : list_[i]) {
                if (!used[{i, edge.first}] && !used[{edge.first, i}]) {
                    file << edge.first + 1 << ' ' << edge.second << ' ';
                    // used[{i, edge.first}] = true;
                    // used[{edge.first, i}] = true;
                }
            }
            file.seekp(-1, std::ofstream::cur);
            file << '\n';
        }
    } else {
        for (int i = 0; i < list_.size(); ++i) {
            for (const auto& edge : list_[i]) {
                if (!used[{i, edge.first}] && !used[{edge.first, i}]) {
                    file << edge.first + 1 << ' ';
                    // used[{i, edge.first}] = true;
                    // used[{edge.first, i}] = true;
                }
            }
            file.seekp(-1, std::ofstream::cur);
            file << '\n';
        }
    }
}

void AdjacencyList::addEdge(const int from, const int to, const int weight) {
    if (isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    list_[from_idx].push_back({to_idx, weight});
    if (!directed_) {
        list_[to_idx].push_back({from_idx, weight});
    }
    ++edges_count_;
}

void AdjacencyList::removeEdge(const int from, const int to) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    list_[from_idx].erase(std::remove_if(
        list_[from_idx].begin(), list_[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; }));

    if (!directed_) {
        list_[to_idx].erase(std::remove_if(
            list_[to_idx].begin(), list_[to_idx].end(),
            [from_idx](const auto& edge) { return edge.first == from_idx; }));
    }
    --edges_count_;
}

void AdjacencyList::changeEdge(const int from, const int to, const int weight) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    auto edge_iter = std::find_if(
        list_[from_idx].begin(), list_[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
    if (edge_iter != list_[from_idx].end()) {
        edge_iter->second = weight;
    }

    if (!directed_) {
        edge_iter = std::find_if(
            list_[to_idx].begin(), list_[to_idx].end(),
            [from_idx](const auto& edge) { return edge.first == from_idx; });
        if (edge_iter != list_[to_idx].end()) {
            edge_iter->second = weight;
        }
    }
}

void AdjacencyList::printGraph() const {
    std::map<std::pair<int, int>, bool> used;

    std::cout << "Adjacency list:\n";
    if (weighted_) {
        for (int i = 0; i < list_.size(); ++i) {
            std::cout << i + 1 << ": ";
            for (const auto& edge : list_[i]) {
                if (!used[{i, edge.first}] && !used[{edge.first, i}]) {
                    std::cout << edge.first + 1 << ' ' << "(w: " << edge.second
                              << ") ";
                    used[{i, edge.first}] = true;
                    used[{edge.first, i}] = true;
                }
            }
            std::cout << '\n';
        }
    } else {
        for (int i = 0; i < list_.size(); ++i) {
            std::cout << i + 1 << ": ";
            for (const auto& edge : list_[i]) {
                if (!used[{i, edge.first}] && !used[{edge.first, i}]) {
                    std::cout << edge.first + 1 << ' ';
                    used[{i, edge.first}] = true;
                    used[{edge.first, i}] = true;
                }
            }
            std::cout << '\n';
        }
    }
}

void AdjacencyList::clearGraph() {
    list_.clear();
    directed_ = weighted_ = false;
    edges_count_ = 0;
}

int AdjacencyList::getVerticesCount() {
    return list_.size(); }

int AdjacencyList::getEdgesCount() {
    return edges_count_; }

AdjacencyMatrix* AdjacencyList::getNewAdjMatrix() {
    std::vector<std::vector<int>> matrix(list_.size(),
                                         std::vector<int>(list_.size(), 0));
    for (int i = 0; i < list_.size(); ++i) {
        for (const auto& edge : list_[i]) {
            matrix[i][edge.first] = edge.second;
        }
    }
    return new AdjacencyMatrix(std::move(matrix), directed_, weighted_);
}

EdgeList* AdjacencyList::getNewListOfEdges() {
    std::map<std::pair<int, int>, int> edges;
    for (int i = 0; i < list_.size(); ++i) {
        for (const auto& edge : list_[i]) {
            edges[{i, edge.first}] = edge.second;
        }
    }
    return new EdgeList(std::move(edges), directed_, weighted_, list_.size());
}

std::vector<std::vector<std::pair<int, int>>>*
AdjacencyList::getGraphPointer() {
    return &list_;
}

bool AdjacencyList::isVerticeExist(const int vertice) const {
    return vertice >= 0 && vertice < list_.size();
}

bool AdjacencyList::isEdgeExist(const int from, const int to) const {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        return false;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;
    return std::any_of(
        list_[from_idx].begin(), list_[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
}
