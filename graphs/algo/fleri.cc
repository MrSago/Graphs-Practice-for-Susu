#include "fleri.h"

#include <iostream>
#include <stack>
#include <vector>

std::vector<int> Fleri::getEuleranTour(AdjacencyList& graph) {
  adj_list_t adj_list = (*graph.getStructPointer());
  const int vertices_count = graph.getVerticesCount();
  std::vector<int> degree(vertices_count, 0);

  for (int i = 0; i < vertices_count; ++i) {
    degree[i] = adj_list[i].size();
  }

  int start = 1;
  bool circleExist = true;
  int odd = 0;
  for (int i = 0; i < vertices_count; ++i) {
    if (degree[i] & 1) {
      circleExist = false;
      ++odd;
    }
    if (degree[i]) {
      start = i + 1;
    }
  }

  if (!circleExist || odd > 2) {
    return std::vector<int>();
  }

  std::stack<int> st;
  std::vector<int> path;
  st.push(start);
  while (!st.empty()) {
    int u = st.top() - 1;
    if (adj_list[u].empty()) {
      path.push_back(u + 1);
      st.pop();
    } else {
      int v = adj_list[u].back().first - 1;
      adj_list[u].pop_back();
      for (int i = 0; i < adj_list[v].size(); ++i) {
        if (adj_list[v][i].first == u) {
          adj_list[v].erase(adj_list[v].begin() + i);
          break;
        }
      }
      st.push(v + 1);
    }
  }

  if (path.size() != graph.getEdgesCount() + 1) {
    return std::vector<int>();
  }

  return path;
}