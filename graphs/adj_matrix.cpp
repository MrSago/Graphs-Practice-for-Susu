
#include "adj_matrix.hpp"

void AdjacencyMatrix::readGraph(std::ifstream& file) {
    clearGraph();

    int verticesCount;
    file >> verticesCount;
    adjacencyMatrix.resize(verticesCount, std::vector<int>(verticesCount));

    file >> isDirected >> isWeighted;

    for (auto& row : adjacencyMatrix) {
        for (auto& vertice : row) {
            file >> vertice;
        }
    }
}

void AdjacencyMatrix::writeGraph(std::ofstream& file) {
    file << adjacencyMatrix.size() << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    for (const auto& row : adjacencyMatrix) {
        for (const auto& vertice : row) {
            file << vertice << ' ';
        }
        file << '\n';
    }
}

void AdjacencyMatrix::addEdge(const int from, const int to, const int weight) {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        std::cerr << "Vertice doesn't exist\n";
        return;
    }

    if (isEdgeExist(from, to)) {
        std::cerr << "Edge already exist\n";
        return;
    }

    adjacencyMatrix[from][to] = weight;
    if (!isDirected) {
        adjacencyMatrix[to][from] = weight;
    }
}

void AdjacencyMatrix::removeEdge(const int from, const int to) {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        std::cerr << "Vertice doesn't exist\n";
        return;
    }

    if (!isEdgeExist(from, to)) {
        std::cerr << "Edge doesn't exist\n";
        return;
    }

    adjacencyMatrix[from][to] = 0;
    if (!isDirected) {
        adjacencyMatrix[to][from] = 0;
    }
}

void AdjacencyMatrix::changeEdge(const int from, const int to,
                                 const int weight) {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        std::cerr << "Vertice doesn't exist\n";
        return;
    }

    if (!isEdgeExist(from, to)) {
        std::cerr << "Edge doesn't exist\n";
        return;
    }

    adjacencyMatrix[from][to] = weight;
    if (!isDirected) {
        adjacencyMatrix[to][from] = weight;
    }
}

void AdjacencyMatrix::printGraph() const {
    std::cout << "Adjacency matrix:\n";
    for (const auto& row : adjacencyMatrix) {
        for (const auto& vertice : row) {
            std::cout << std::setw(3) << vertice << ' ';
        }
        std::cout << '\n';
    }
}

void AdjacencyMatrix::clearGraph() {
    adjacencyMatrix.clear();
    isDirected = isWeighted = false;
}

bool AdjacencyMatrix::isVerticeExist(const int vertice) const {
    return vertice >= 0 && vertice < adjacencyMatrix.size();
}

bool AdjacencyMatrix::isEdgeExist(const int from, const int to) const {
    return adjacencyMatrix[from][to] != 0;
}
