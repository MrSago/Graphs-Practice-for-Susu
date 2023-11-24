#ifndef FLERI_H
#define FLERI_H

#include "adj_list.h"

class Fleri {
 public:
  std::vector<int> getEuleranTour(AdjacencyList& graph);
};

#endif // FLERI_H
