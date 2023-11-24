#ifndef EULER_CIRCLE_H
#define EULER_CIRCLE_H

#include "adj_list.h"

class EulerCircle {
 public:
  int checkEuler(AdjacencyList& graph, bool& circleExist);

 private:
  adj_list_t list;
  int vertices_count;
  std::vector<bool> used;

  bool checkComps();
  void dfs(int v);
};

#endif  // EULER_CIRCLE_H