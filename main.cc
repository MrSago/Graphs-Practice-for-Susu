
#include "graph.h"
#include "graph_test.hpp"

int main() {
  // freopen("et1.out", "w", stdout);

  // Graph graph;
  // graph.readGraph("et1.in");

  // bool circleExist = false;
  // int v = graph.checkEuler(circleExist);

  // if (v == 0) {
  //   std::cout << "0\n";
  //   exit(0);
  // } else {
  //   //  std::vector<int> path = graph.getEuleranTourEffective();
  //   std::vector<int> path = graph.getEuleranTourFleri();

  //   std::cout << path[0] << "\n";
  //   for (int i = 0; i < path.size(); ++i) {
  //     std::cout << path[i] << ((i + 1 < path.size()) ? " " : "\n");
  //   }
  // }

  GraphTest test;
  test.runEuleranTourTest();

  return 0;
}
