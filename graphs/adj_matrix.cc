
#include "adj_matrix.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "adj_list.h"
#include "edge_list.h"
#include "graph_representation.h"

AdjacencyMatrix::AdjacencyMatrix(const std::vector<std::vector<int>>&& matrix,
                                 const bool directed, const bool weighted)
    : matrix_(matrix), directed_(directed), weighted_(weighted) {}

void AdjacencyMatrix::readGraph(std::ifstream& file) {
    clearGraph();

    int vertices_count;
    file >> vertices_count;
    matrix_.resize(vertices_count, std::vector<int>(vertices_count, 0));

    file >> directed_ >> weighted_;

    for (auto& row : matrix_) {
        for (auto& vertice : row) {
            file >> vertice;
            edges_count_ += bool(vertice);
        }
    }

    if (!directed_) {
        edges_count_ >>= 1;
    }
}

void AdjacencyMatrix::writeGraph(std::ofstream& file) {
    file << matrix_.size() << '\n';
    file << directed_ << ' ' << weighted_ << '\n';

    for (const auto& row : matrix_) {
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

    matrix_[from_idx][to_idx] = weight;
    if (!directed_) {
        matrix_[to_idx][from_idx] = weight;
    }
    ++edges_count_;
}

void AdjacencyMatrix::removeEdge(const int from, const int to) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix_[from_idx][to_idx] = 0;
    if (!directed_) {
        matrix_[to_idx][from_idx] = 0;
    }
    --edges_count_;
}

void AdjacencyMatrix::changeEdge(const int from, const int to,
                                 const int weight) {
    if (!isEdgeExist(from, to)) {
        return;
    }

    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix_[from_idx][to_idx] = weight;
    if (!directed_) {
        matrix_[to_idx][from_idx] = weight;
    }
}

void AdjacencyMatrix::printGraph() const {
    std::cout << "Adjacency matrix:\n";
    for (const auto& row : matrix_) {
        for (const auto& vertice : row) {
            std::cout << vertice << ' ';
        }
        std::cout << '\n';
    }
}

void AdjacencyMatrix::clearGraph() {
    matrix_.clear();
    directed_ = weighted_ = false;
    edges_count_ = 0;
}

int AdjacencyMatrix::getVerticesCount() { return matrix_.size(); }

int AdjacencyMatrix::getEdgesCount() { return edges_count_; }

AdjacencyList* AdjacencyMatrix::getNewAdjList() {
    std::vector<std::vector<std::pair<int, int>>> list(matrix_.size());
    for (int i = 0; i < matrix_.size(); ++i) {
        for (int j = 0; j < matrix_.size(); ++j) {
            if (matrix_[i][j]) {
                list[i].push_back({j, matrix_[i][j]});
            }
        }
    }
    return new AdjacencyList(std::move(list), directed_, weighted_);
}

EdgeList* AdjacencyMatrix::getNewListOfEdges() {
    std::map<std::pair<int, int>, int> edges;
    for (int i = 0; i < matrix_.size(); ++i) {
        for (int j = 0; j < matrix_.size(); ++j) {
            if (matrix_[i][j]) {
                edges[{i, j}] = matrix_[i][j];
            }
        }
    }
    return new EdgeList(std::move(edges), directed_, weighted_, matrix_.size());
}

std::vector<std::vector<int>>* AdjacencyMatrix::getGraphPointer() {
    return &matrix_;
}

bool AdjacencyMatrix::isVerticeExist(const int vertice) const {
    return vertice > 0 && vertice <= matrix_.size();
}

bool AdjacencyMatrix::isEdgeExist(const int from, const int to) const {
    return isVerticeExist(from) && isVerticeExist(to) &&
           matrix_[from - 1][to - 1];
}
