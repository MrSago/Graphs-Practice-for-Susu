
#include "adj_matrix.hpp"

#include <fstream>
#include <iostream>
#include <vector>

AdjacencyMatrix::AdjacencyMatrix(const std::vector<std::vector<int>>&& matrix,
                                 const bool isDirected, const bool isWeighted)
    : matrix(matrix), isDirected(isDirected), isWeighted(isWeighted) {}

void AdjacencyMatrix::readGraph(std::ifstream& file) {
    clearGraph();

    int verticesCount;
    file >> verticesCount;
    matrix.resize(verticesCount, std::vector<int>(verticesCount, 0));

    file >> isDirected >> isWeighted;

    for (auto& row : matrix) {
        for (auto& vertice : row) {
            file >> vertice;
            if (vertice) {
                ++edgesCount;
            }
        }
    }

    if (!isDirected) {
        edgesCount /= 2;
    }
}

void AdjacencyMatrix::writeGraph(std::ofstream& file) {
    file << matrix.size() << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    for (const auto& row : matrix) {
        for (const auto& vertice : row) {
            file << vertice << ' ';
        }
        file.seekp(-1, std::ofstream::cur);
        file << '\n';
    }
}

void AdjacencyMatrix::addEdge(const int from, const int to, const int weight) {
    if (isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix[from_idx][to_idx] = weight;
    if (!isDirected) {
        matrix[to_idx][from_idx] = weight;
    }
    ++edgesCount;
}

void AdjacencyMatrix::removeEdge(const int from, const int to) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix[from_idx][to_idx] = 0;
    if (!isDirected) {
        matrix[to_idx][from_idx] = 0;
    }
    --edgesCount;
}

void AdjacencyMatrix::changeEdge(const int from, const int to,
                                 const int weight) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix[from_idx][to_idx] = weight;
    if (!isDirected) {
        matrix[to_idx][from_idx] = weight;
    }
}

void AdjacencyMatrix::printGraph() const {
    std::cout << "Adjacency matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& vertice : row) {
            std::cout << vertice << ' ';
        }
        std::cout << '\n';
    }
}

void AdjacencyMatrix::clearGraph() {
    matrix.clear();
    isDirected = isWeighted = false;
    edgesCount = 0;
}

int AdjacencyMatrix::getVerticesCount() { return matrix.size(); }

int AdjacencyMatrix::getEdgesCount() { return edgesCount; }

AdjacencyList* AdjacencyMatrix::getNewAdjList() {
    std::vector<std::vector<std::pair<int, int>>> list(matrix.size());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j]) {
                list[i].push_back({j, matrix[i][j]});
            }
        }
    }
    return new AdjacencyList(std::move(list), isDirected, isWeighted);
}

EdgeList* AdjacencyMatrix::getNewListOfEdges() {
    std::map<std::pair<int, int>, int> edges;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j]) {
                edges[{i, j}] = matrix[i][j];
            }
        }
    }
    return new EdgeList(std::move(edges), isDirected, isWeighted,
                        matrix.size());
}

std::vector<std::vector<int>>* AdjacencyMatrix::getGraphPointer() { return &matrix; }

bool AdjacencyMatrix::isVerticeExist(const int vertice) const {
    return vertice > 0 && vertice <= matrix.size();
}

bool AdjacencyMatrix::isEdgeExist(const int from, const int to) const {
    return isVerticeExist(from) && isVerticeExist(to) &&
           matrix[from - 1][to - 1];
}
