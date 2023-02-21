
#include "graph.h"
#include "graph_test.hpp"

int main() {
    GraphTest test;
    test.runUnitTests("1e3_1e5.in");
    // test.runUnitTests("1e4_1e5.in");
    // test.runUnitTests("1e5_1e5.in");
    test.runPrimTests();
    test.runKruscalTests();
    return 0;
}
