
#include "adj_list.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

AdjacencyList::AdjacencyList(
    const std::vector<std::vector<std::pair<int, int>>>&& list,
    const bool isDirected, const bool isWeighted)
    : list(list), isDirected(isDirected), isWeighted(isWeighted) {}

void AdjacencyList::readGraph(std::ifstream& file) {
    clearGraph();

    int verticesCount;
    file >> verticesCount;
    list.resize(verticesCount);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    file >> isDirected >> isWeighted;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (isWeighted) {
        int from_idx, to, weight;
        from_idx = to = weight = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            while (iss >> to >> weight) {
                list[from_idx].push_back({to - 1, weight});
                // if (!isDirected) {
                //     list[to - 1].push_back({from_idx, weight});
                // }
                ++edgesCount;
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
                list[from_idx].push_back({to - 1, 1});
                // if (!isDirected) {
                //     list[to - 1].push_back({from_idx, 1});
                // }
                ++edgesCount;
            }
            ++from_idx;
        }
    }
}

void AdjacencyList::writeGraph(std::ofstream& file) {
    std::map<std::pair<int, int>, bool> used;

    file << list.size() << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    if (isWeighted) {
        for (int i = 0; i < list.size(); ++i) {
            for (const auto& edge : list[i]) {
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
        for (int i = 0; i < list.size(); ++i) {
            for (const auto& edge : list[i]) {
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

    list[from_idx].push_back({to_idx, weight});
    if (!isDirected) {
        list[to_idx].push_back({from_idx, weight});
    }
    ++edgesCount;
}

void AdjacencyList::removeEdge(const int from, const int to) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    list[from_idx].erase(std::remove_if(
        list[from_idx].begin(), list[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; }));

    if (!isDirected) {
        list[to_idx].erase(std::remove_if(
            list[to_idx].begin(), list[to_idx].end(),
            [from_idx](const auto& edge) { return edge.first == from_idx; }));
    }
    --edgesCount;
}

void AdjacencyList::changeEdge(const int from, const int to, const int weight) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    auto edge_iter = std::find_if(
        list[from_idx].begin(), list[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
    if (edge_iter != list[from_idx].end()) {
        edge_iter->second = weight;
    }

    if (!isDirected) {
        edge_iter = std::find_if(
            list[to_idx].begin(), list[to_idx].end(),
            [from_idx](const auto& edge) { return edge.first == from_idx; });
        if (edge_iter != list[to_idx].end()) {
            edge_iter->second = weight;
        }
    }
}

void AdjacencyList::printGraph() const {
    std::map<std::pair<int, int>, bool> used;

    std::cout << "Adjacency list:\n";
    if (isWeighted) {
        for (int i = 0; i < list.size(); ++i) {
            std::cout << i + 1 << ": ";
            for (const auto& edge : list[i]) {
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
        for (int i = 0; i < list.size(); ++i) {
            std::cout << i + 1 << ": ";
            for (const auto& edge : list[i]) {
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
    list.clear();
    isDirected = isWeighted = false;
    edgesCount = 0;
}

int AdjacencyList::getVerticesCount() { return list.size(); }

int AdjacencyList::getEdgesCount() { return edgesCount; }

AdjacencyMatrix* AdjacencyList::getNewAdjMatrix() {
    std::vector<std::vector<int>> matrix(list.size(),
                                         std::vector<int>(list.size(), 0));
    for (int i = 0; i < list.size(); ++i) {
        for (const auto& edge : list[i]) {
            matrix[i][edge.first] = edge.second;
        }
    }
    return new AdjacencyMatrix(std::move(matrix), isDirected, isWeighted);
}

EdgeList* AdjacencyList::getNewListOfEdges() {
    std::map<std::pair<int, int>, int> edges;
    for (int i = 0; i < list.size(); ++i) {
        for (const auto& edge : list[i]) {
            edges[{i, edge.first}] = edge.second;
        }
    }
    return new EdgeList(std::move(edges), isDirected, isWeighted, list.size());
}

std::vector<std::vector<std::pair<int, int>>>& AdjacencyList::getList() {
    return list;
}

bool AdjacencyList::isVerticeExist(const int vertice) const {
    return vertice >= 0 && vertice < list.size();
}

bool AdjacencyList::isEdgeExist(const int from, const int to) const {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        return false;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;
    return std::any_of(
        list[from_idx].begin(), list[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
}
