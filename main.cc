
#include "graph.h"
#include "graph_test.hpp"

int main() {
    GraphTest test;
    // test.runUnitTests("1e3_1e5.in");
    // test.runUnitTests("1e4_1e5.in");
    // test.runUnitTests("1e5_1e5.in");
    test.runBoruvkiTests();
    test.runPrimTests();
    test.runKruscalTests();

    // Graph g;
    // g.readGraph("1.txt");
    // g.printGraph();
    // Graph gg = g.getSpaingTreeKruscal();
    // gg.printGraph();

    return 0;
}
