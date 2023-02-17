
#include "edge_list.hpp"

#include <fstream>
#include <iostream>
#include <map>

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
        }
    } else {
        while (edgeCount--) {
            int from, to;
            file >> from >> to;
            edges[{from - 1, to - 1}] = 1;
        }
    }
}

void EdgeList::writeGraph(std::ofstream& file) {
    file << verticesCount << ' ' << edges.size() << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    if (isWeighted) {
        for (const auto& [edge, weight] : edges) {
            if (weight) {
                file << edge.first + 1 << ' ' << edge.second + 1 << ' '
                     << weight << '\n';
            }
        }
    } else {
        for (const auto& [edge, weight] : edges) {
            if (weight) {
                file << edge.first + 1 << ' ' << edge.second + 1 << '\n';
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
    std::cout << "Edges list:\n";
    if (isWeighted) {
        for (const auto& [edge, weight] : edges) {
            if (weight) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << " (weight: " << weight << ")\n";
            }
        }
    } else {
        for (const auto& [edge, weight] : edges) {
            if (weight) {
                std::cout << edge.first + 1 << " -> " << edge.second + 1
                          << '\n';
            }
        }
    }
}

void EdgeList::clearGraph() {
    edges.clear();
    verticesCount = 0;
    isDirected = isWeighted = false;
}

AdjacencyMatrix* EdgeList::getAdjMatrix() {
    std::vector<std::vector<int>> matrix(verticesCount,
                                         std::vector<int>(verticesCount, 0));
    for (const auto& [edge, weight] : edges) {
        matrix[edge.first][edge.second] = weight;
    }
    return new AdjacencyMatrix(std::move(matrix), isDirected, isWeighted);
}

AdjacencyList* EdgeList::getAdjList() {
    std::vector<std::vector<std::pair<int, int>>> list(verticesCount);
    for (const auto& [edge, weight] : edges) {
        list[edge.first].push_back({edge.second, weight});
    }
    return new AdjacencyList(std::move(list), isDirected, isWeighted);
}

bool EdgeList::isVerticeExist(const int vertice) const {
    return vertice > 0 && vertice <= verticesCount;
}

bool EdgeList::isEdgeExist(const int from, const int to) const {
    return isVerticeExist(from) && isVerticeExist(to) &&
           edges.at({from - 1, to - 1});
}
