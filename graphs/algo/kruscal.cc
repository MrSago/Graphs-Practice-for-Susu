
#include "kruscal.h"

#include <algorithm>
#include <map>
#include <vector>

#include "dsu.h"
#include "edge_list.h"

EdgeList* Kruscal::getSpaingTree(EdgeList& graph) {
    const edge_list_t& edges = (*graph.getStructPointer());
    const int vertices_count = graph.getVerticesCount();
    const int edges_count = graph.getEdgesCount();

    std::vector<std::pair<int, std::pair<int, int>>> copied_graph;
    copied_graph.reserve(edges_count);
    std::for_each(edges.begin(), edges.end(), [&copied_graph](auto& edge) {
        copied_graph.push_back(
            {edge.second, {edge.first.first, edge.first.second}});
    });
    std::sort(copied_graph.begin(), copied_graph.end());

    EdgeList* result = new EdgeList(vertices_count, false, true);
    DSU dsu(vertices_count);

    for (int i = 0; i < edges_count; ++i) {
        int x = copied_graph[i].second.first;
        int y = copied_graph[i].second.second;
        int w = copied_graph[i].first;
        if (dsu.find(x) != dsu.find(y)) {
            result->addEdge(x + 1, y + 1, w);
            dsu.unite(x, y);
        }
    }

    return result;
}
