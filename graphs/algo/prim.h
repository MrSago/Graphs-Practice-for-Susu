
#ifndef PRIM_H
#define PRIM_H

#include "adj_matrix.h"
#include "edge_list.h"

class Prim {
   public:
    EdgeList* getSpaingTreeDenseGraph(AdjacencyMatrix& graph);
    EdgeList* getSpaingTreeSparseGraph(AdjacencyList& graph);
};

#endif  // PRIM_H
