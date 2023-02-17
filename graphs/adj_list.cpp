
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
        int from, to, weight;
        from = to = weight = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            while (iss >> to >> weight) {
                list[from].push_back({to - 1, weight});
            }
            ++from;
        }
    } else {
        int from, to;
        from = to = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            while (iss >> to) {
                list[from].push_back({to - 1, 1});
            }
            ++from;
        }
    }
}

void AdjacencyList::writeGraph(std::ofstream& file) {
    file << list.size() << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    if (isWeighted) {
        for (int i = 0; i < list.size(); ++i) {
            for (const auto& edge : list[i]) {
                file << edge.first + 1 << ' ' << edge.second << ' ';
            }
            file.seekp(-1, std::ofstream::cur);
            file << '\n';
        }
    } else {
        for (int i = 0; i < list.size(); ++i) {
            for (const auto& edge : list[i]) {
                file << edge.first + 1 << ' ';
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
}

void AdjacencyList::changeEdge(const int from, const int to, const int weight) {
    int from_idx = from - 1;
    int to_idx = to - 1;

    auto edge_iter = std::find_if(
        list[from_idx].begin(), list[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
    if (edge_iter != list[from_idx].end()) {
        edge_iter->first = weight;
    }

    if (!isDirected) {
        edge_iter = std::find_if(
            list[to_idx].begin(), list[to_idx].end(),
            [from_idx](const auto& edge) { return edge.first == from_idx; });
        if (edge_iter != list[to_idx].end()) {
            edge_iter->first = weight;
        }
    }
}

void AdjacencyList::printGraph() const {
    std::cout << "Adjacency list:\n";
    if (isWeighted) {
        for (int i = 0; i < list.size(); ++i) {
            std::cout << i << ": ";
            for (const auto& edge : list[i]) {
                std::cout << edge.first << ' ' << "(w: " << edge.second << ") ";
            }
            std::cout << '\n';
        }
    } else {
        for (int i = 0; i < list.size(); ++i) {
            std::cout << i << ": ";
            for (const auto& edge : list[i]) {
                std::cout << edge.first << ' ';
            }
            std::cout << '\n';
        }
    }
}

void AdjacencyList::clearGraph() {
    list.clear();
    isDirected = false;
    isWeighted = false;
}

AdjacencyMatrix* AdjacencyList::getAdjMatrix() {
    std::vector<std::vector<int>> matrix(list.size(),
                                         std::vector<int>(list.size(), 0));
    for (int i = 0; i < list.size(); ++i) {
        for (const auto& edge : list[i]) {
            matrix[i][edge.first] = edge.second;
        }
    }
    return new AdjacencyMatrix(std::move(matrix), isDirected, isWeighted);
}

EdgeList* AdjacencyList::getListOfEdges() {
    std::map<std::pair<int, int>, int> edges;
    for (int i = 0; i < list.size(); ++i) {
        for (const auto& edge : list[i]) {
            edges[{i, edge.first}] = edge.second;
        }
    }
    return new EdgeList(std::move(edges), isDirected, isWeighted, list.size());
}

bool AdjacencyList::isVerticeExist(const int vertice) const {
    return vertice >= 0 && vertice < list.size();
}

bool AdjacencyList::isEdgeExist(const int from, const int to) const {
    int from_idx = from - 1;
    int to_idx = to - 1;
    return std::any_of(
        list[from_idx].begin(), list[from_idx].end(),
        [to_idx](const auto& edge) { return edge.first == to_idx; });
}
