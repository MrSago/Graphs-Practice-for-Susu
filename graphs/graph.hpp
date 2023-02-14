
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "adj_list.hpp"
#include "adj_matrix.hpp"
//#include "edje_list.hpp"
#include "graph_representation.hpp"

enum class GraphType : char {
    AdjacencyMatrix = 'C',
    AdjacencyList = 'L',
    EdgeList = 'E',
    Unknown = 'U'
};

class Graph {
   public:
    Graph();
    ~Graph();

    void readGraph(const std::string& fileName);
    void writeGraph(const std::string& fileName);
    void addEdge(const int from, const int to, const int weight);
    void removeEdge(const int from, const int to);
    void changeEdge(const int from, const int to, const int weight);
    void printGraph();
    void clearGraph();

    // void transformToAdjMatrix();
    // void transformToAdjList();
    // void transformToListOfEdges();

   private:
    GraphType graphType = GraphType::Unknown;
    std::map<GraphType, GraphRepresentation*> graphRepr;
};

#endif  // GRAPH_HPP
