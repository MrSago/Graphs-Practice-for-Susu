
#include "adj_matrix.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "adj_list.h"
#include "edge_list.h"
#include "graph_representation.h"

AdjacencyMatrix::AdjacencyMatrix(const int vertices_count, const bool directed,
                                 const bool weighted)
    : matrix_(vertices_count, std::vector<int>(vertices_count, 0)),
      edges_count_(0),
      directed_(directed),
      weighted_(weighted) {}

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
    int from_idx = from - 1;
    int to_idx = to - 1;

    matrix_[from_idx][to_idx] = weight;
    if (!directed_) {
        matrix_[to_idx][from_idx] = weight;
    }
    ++edges_count_;
}

void AdjacencyMatrix::removeEdge(const int from, const int to) {
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
    edges_count_ = 0;
    directed_ = weighted_ = false;
}

int AdjacencyMatrix::getVerticesCount() { return matrix_.size(); }

int AdjacencyMatrix::getEdgesCount() { return edges_count_; }

adj_matrix_t* AdjacencyMatrix::getStructPointer() { return &matrix_; }

AdjacencyList* AdjacencyMatrix::getNewAdjList() {
    const int vertices_count = getVerticesCount();
    AdjacencyList* adj_list =
        new AdjacencyList(directed_, weighted_, vertices_count);
    for (int i = 0; i < vertices_count; ++i) {
        for (int j = 0; j < vertices_count; ++j) {
            if (matrix_[i][j]) {
                adj_list->addEdge(i + 1, j + 1, matrix_[i][j]);
            }
        }
    }
    return adj_list;
}

EdgeList* AdjacencyMatrix::getNewListOfEdges() {
    const int vertices_count = getVerticesCount();
    EdgeList* edge_list = new EdgeList(directed_, weighted_, vertices_count);
    for (int i = 0; i < vertices_count; ++i) {
        for (int j = 0; j < vertices_count; ++j) {
            if (matrix_[i][j]) {
                edge_list->addEdge(i + 1, j + 1, matrix_[i][j]);
            }
        }
    }
    return edge_list;
}
