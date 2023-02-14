
#include "graph.hpp"

int main() {
    Graph graph;
    graph.readGraph("test2.txt");
    graph.printGraph();
    graph.writeGraph("output2.txt");
    return 0;
}
