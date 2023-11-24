#include "euler_circle.h"

#include <iostream>
#include <stack>
#include <vector>

int EulerCircle::checkEuler(AdjacencyList& graph, bool& circleExist) {
  list = (*graph.getStructPointer());
  vertices_count = graph.getVerticesCount();
  used.resize(vertices_count, false);

  bool euleran = checkComps();
  if (!euleran) {
    circleExist = false;
    return 0;
  }

  int start = 1;
  circleExist = true;
  int odd = 0;
  for (int i = 0; i < vertices_count; ++i) {
    int degree = list[i].size();
    if (degree & 1) {
      circleExist = false;
      ++odd;
    }
    if (degree) {
      start = i + 1;
    }
  }

  return (circleExist || odd <= 2 ? start : 0);
}

bool EulerCircle::checkComps() {
  int comp_count = 0;
  for (int i = 0; i < vertices_count; ++i) {
    if (!used[i]) {
      if (list[i].size() == 0) {
        used[i] = true;
        continue;
      }

      if (comp_count++ > 0) {
        return false;
      }

      dfs(i + 1);
    }
  }
  return true;
}

void EulerCircle::dfs(int v) {
  used[--v] = true;
  for (int i = 0; i < list[v].size(); ++i) {
    int to = list[v][i].first;
    if (!used[to]) {
      dfs(to + 1);
    }
  }
}