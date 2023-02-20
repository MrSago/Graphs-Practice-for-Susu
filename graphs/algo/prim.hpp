
#ifndef PRIM_HPP
#define PRIM_HPP

#include <map>
#include <vector>

#include "adj_matrix.hpp"
#include "edge_list.hpp"

class Prim {
   public:
    EdgeList* getSpaingTreeDenseGraph(AdjacencyMatrix* adjMatrix);
    EdgeList* getSpaingTreeSparseGraph(AdjacencyList* adjList);

   private:
    const int INF = int(1e9);
};

#endif  // PRIM_HPP
