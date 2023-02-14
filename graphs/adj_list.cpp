
#include "adj_list.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

void AdjacencyList::readGraph(std::ifstream& file) {
    clearGraph();

    file >> verticesCount;
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
                addEdge(from, to, weight);
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
                addEdge(from, to);
            }
            ++from;
        }
    }
}

void AdjacencyList::writeGraph(std::ofstream& file) {
    file << verticesCount << '\n';
    file << isDirected << ' ' << isWeighted << '\n';

    if (isWeighted) {
        int from = 0;
        for (const auto& [edje, weight] : adjacencyList) {
            if (edje.first != from) {
                file << '\n';
                from = edje.first;
            }
            file << edje.second << ' ' << weight << ' ';
        }
    } else {
        int from = 0;
        for (const auto& [edje, weight] : adjacencyList) {
            if (edje.first != from) {
                file << '\n';
                from = edje.first;
            }
            file << edje.second << ' ';
        }
    }
}

void AdjacencyList::addEdge(const int from, const int to, const int weight) {
    if (from < 0 || from >= verticesCount || to < 0 || to >= verticesCount) {
        std::cerr << "Vertices out of range\n";
        return;
    }

    adjacencyList[{from, to}] = weight;
    if (!isDirected) {
        adjacencyList[{to, from}] = weight;
    }
}

void AdjacencyList::removeEdge(const int from, const int to) {
    if (!isEdgeExist(from, to)) {
        std::cerr << "Edge doesn't exist\n";
        return;
    }

    adjacencyList.erase({from, to});
    if (!isDirected) {
        adjacencyList.erase({to, from});
    }
}

void AdjacencyList::changeEdge(const int from, const int to, const int weight) {
    if (!isEdgeExist(from, to)) {
        std::cerr << "Edge doesn't exist\n";
        return;
    }

    adjacencyList[{from, to}] = weight;
    if (!isDirected) {
        adjacencyList[{to, from}] = weight;
    }
}

void AdjacencyList::printGraph() const {
    std::cout << "Adjacency list:\n";
    for (const auto& [edje, weight] : adjacencyList) {
        std::cout << edje.first << " -> " << edje.second;
        if (isWeighted) {
            std::cout << " (weight: " << weight << ')';
        }
        std::cout << '\n';
    }
}

void AdjacencyList::clearGraph() {
    adjacencyList.clear();
    isDirected = isWeighted = false;
}

bool AdjacencyList::isVerticeExist(const int vertice) const {
    if (vertice > 0 && vertice < verticesCount) {
        for (const auto& [edje, weight] : adjacencyList) {
            if (edje.first == vertice) {
                return true;
            }
        }
    }
    return false;
}

bool AdjacencyList::isEdgeExist(const int from, const int to) const {
    if (!isVerticeExist(from) || !isVerticeExist(to)) {
        return false;
    }

    for (const auto& [edje, weight] : adjacencyList) {
        if (edje.first == from && edje.second == to) {
            return true;
        }
    }
    return false;
}
