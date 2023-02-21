
#ifndef GRAPH_REPRESENTATION_H
#define GRAPH_REPRESENTATION_H

#include <fstream>

class GraphRepresentation {
   public:
    virtual void readGraph(std::ifstream& file) = 0;
    virtual void writeGraph(std::ofstream& file) = 0;
    virtual void addEdge(const int from, const int to,
                         const int weight = 1) = 0;
    virtual void removeEdge(const int from, const int to) = 0;
    virtual void changeEdge(const int from, const int to, const int weight) = 0;

    virtual void printGraph() const = 0;
    virtual void clearGraph() = 0;
    virtual int getVerticesCount() = 0;
    virtual int getEdgesCount() = 0;

    virtual ~GraphRepresentation() = default;
};

#endif  // GRAPH_REPRESENTATION_H
