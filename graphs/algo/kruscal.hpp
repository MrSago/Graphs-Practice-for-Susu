
#ifndef KRUSCAL_HPP
#define KRUSCAL_HPP

#include <map>
#include <vector>

#include "adj_matrix.hpp"
#include "edge_list.hpp"

class Kruscal {
   public:
    EdgeList* getSpaingTreeDenseGraph(AdjacencyMatrix* adjMatrix);
    EdgeList* getSpaingTreeSparseGraph(AdjacencyList* adjList);

   private:
    const int INF = int(1e9);
};

#endif  // KRUCAL_HPP
