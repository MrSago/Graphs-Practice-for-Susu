
#ifndef KRUSCAL_HPP
#define KRUSCAL_HPP

#include <map>
#include <vector>

#include "adj_matrix.hpp"
#include "edge_list.hpp"

class Kruscal {
   public:
    EdgeList* getSpaingTreeDenseGraph(AdjacencyMatrix& adjMatrix);
    EdgeList* getSpaingTreeSparseGraph(AdjacencyList& adjList);
};

#endif  // KRUCAL_HPP
