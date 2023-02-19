
#include "graph.hpp"
#include "graph_test.hpp"

int main() {
    GraphTest test;
    // test.runUnitTests("input_1e3_1e5.txt");
    // test.runUnitTests("input_1e4_1e5.txt");
    // test.runUnitTests("input_1e5_1e5.txt");
    test.runKruscalTests();
    return 0;
}
