
#include "graph.hpp"

Graph::Graph() {
    graphRepr[GraphType::AdjacencyMatrix] = new AdjacencyMatrix();
    graphRepr[GraphType::AdjacencyList] = new AdjacencyList();
    // graphRepr[GraphType::EdgeList] = new EdgeList();
}

Graph::~Graph() {
    for (auto& graph : graphRepr) {
        delete graph.second;
    }
}

void Graph::readGraph(const std::string& fileName) {
    std::ifstream file(fileName);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << fileName << '\n';
        return;
    }

    char type;
    file >> type;
    // file.ignore();
    graphType = static_cast<GraphType>(type);

    graphRepr[graphType]->readGraph(file);
}

void Graph::writeGraph(const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.fail() || !file.is_open()) {
        std::cerr << "Error opening file: " << fileName << '\n';
        return;
    }

    file << static_cast<char>(graphType) << ' ';

    graphRepr[graphType]->writeGraph(file);
}

void Graph::addEdge(const int from, const int to, const int weight) {
    graphRepr[graphType]->addEdge(from, to, weight);
}

void Graph::removeEdge(const int from, const int to) {
    graphRepr[graphType]->removeEdge(from, to);
}

void Graph::changeEdge(const int from, const int to, const int weight) {
    graphRepr[graphType]->changeEdge(from, to, weight);
}

void Graph::printGraph() { graphRepr[graphType]->printGraph(); }

void Graph::clearGraph() { graphRepr[graphType]->clearGraph(); }
