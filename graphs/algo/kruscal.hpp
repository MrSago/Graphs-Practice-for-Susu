
#ifndef KRUSCAL_HPP
#define KRUSCAL_HPP

#include "DSU.hpp"
#include "edge_list.hpp"

class Kruscal {
   public:
    EdgeList* getSpaingTree(EdgeList* edgeList);
};

#endif  // KRUSCAL_HPP
