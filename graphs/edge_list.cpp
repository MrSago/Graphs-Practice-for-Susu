
#include "edge_list.hpp"

#include <fstream>
#include <iostream>
#include <map>

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "graph_representation.hpp"

EdgeList::EdgeList(const std::map<std::pair<int, int>, int>&& edges,
                   const bool isDirected, const bool isWeighted,
                   const int verticesCount)
    : edges(edges),
      isDirected(isDirected),
      isWeighted(isWeighted),
      verticesCount(verticesCount) {}

void EdgeList::readGraph(std::ifstream& file) {
    clearGraph();

    file >> verticesCount;

    int edgeCount;
    file >> edgeCount;

    file >> isDirected >> isWeighted;

    if (isWeighted) {
        while (edgeCount--) {
            int from, to, weight;
            file >> from >> to >> weight;
            edges[{from - 1, to - 1}] = weight;
            if (!isDirected) {
                edges[{to - 1, from - 1}] = weight;
            }
        }
    } else {
        while (edgeCount--) {
            int from, to;
            file >> from >> to;
            edges[{from - 1, to - 1}] = 1;
            if (!isDirected) {
                edges[{to - 1, from - 1}] = 1;
            }
        }
    }
}

void EdgeList::writeGraph(std::ofstream& file) {
    std::map<std::pair<int, int>, bool> used;

    file << verticesCount << ' '
         << (isDirected ? edges.size() : edges.size() / 2) << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    if (isWeighted) {
        for (const auto& [edge, weight] : edges) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                file << edge.first + 1 << ' ' << edge.second + 1 << ' '
                     << weight << '\n';
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges) {
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

    edges[{from_idx, to_idx}] = weight;
    if (!isDirected) {
        edges[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::removeEdge(const int from, const int to) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    edges[{from_idx, to_idx}] = 0;
    if (!isDirected) {
        edges[{to_idx, from_idx}] = 0;
    }
}

void EdgeList::changeEdge(const int from, const int to, const int weight) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    edges[{from_idx, to_idx}] = weight;
    if (!isDirected) {
        edges[{to_idx, from_idx}] = weight;
    }
}

void EdgeList::printGraph() const {
    std::map<std::pair<int, int>, bool> used;
    std::cout << "Edges list:\n";
    if (isWeighted) {
        for (const auto& [edge, weight] : edges) {
            if (weight && !used[{edge.first, edge.second}] &&
                !used[{edge.second, edge.first}]) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << " (w: " << weight << ")\n";
                used[{edge.first, edge.second}] = true;
                used[{edge.second, edge.first}] = true;
            }
        }
    } else {
        for (const auto& [edge, weight] : edges) {
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
    edges.clear();
    verticesCount = 0;
    isDirected = isWeighted = false;
}

int EdgeList::getVerticesCount() { return verticesCount; }

int EdgeList::getEdgesCount() { return edges.size(); }

AdjacencyMatrix* EdgeList::getNewAdjMatrix() {
    std::vector<std::vector<int>> matrix(verticesCount,
                                         std::vector<int>(verticesCount, 0));
    for (const auto& [edge, weight] : edges) {
        matrix[edge.first][edge.second] = weight;
    }
    return new AdjacencyMatrix(std::move(matrix), isDirected, isWeighted);
}

AdjacencyList* EdgeList::getNewAdjList() {
    std::vector<std::vector<std::pair<int, int>>> list(verticesCount);
    for (const auto& [edge, weight] : edges) {
        list[edge.first].push_back({edge.second, weight});
    }
    return new AdjacencyList(std::move(list), isDirected, isWeighted);
}

std::map<std::pair<int, int>, int>* EdgeList::getGraphPointer() {
    return &edges;
}

bool EdgeList::isVerticeExist(const int vertice) const {
    return vertice > 0 && vertice <= verticesCount;
}

bool EdgeList::isEdgeExist(const int from, const int to) const {
    return isVerticeExist(from) && isVerticeExist(to) &&
           edges.at({from - 1, to - 1});
}
