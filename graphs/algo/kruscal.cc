
#include "kruscal.h"

#include <algorithm>
#include <map>
#include <vector>

#include "dsu.h"
#include "edge_list.h"

EdgeList* Kruscal::getSpaingTree(EdgeList& graph) {
    struct edge {
        int w, u, v;
    };

    const edge_list_t& graph_struct = (*graph.getStructPointer());
    const int vertices_count = graph.getVerticesCount();
    const int edges_count = graph.getEdgesCount();

    std::vector<edge> edges;
    edges.reserve(edges_count);
    std::for_each(graph_struct.begin(), graph_struct.end(), [&edges](auto& e) {
        edges.push_back({e.second, e.first.first, e.first.second});
    });
    std::sort(edges.begin(), edges.end(),
              [](auto& f, auto& s) { return f.w < s.w; });

    EdgeList* result = new EdgeList(vertices_count, false, true);
    DSU dsu(vertices_count);

    for (int i = 0; i < edges_count; ++i) {
        int x = edges[i].u;
        int y = edges[i].v;
        int w = edges[i].w;
        if (dsu.find(x) != dsu.find(y)) {
            result->addEdge(x + 1, y + 1, w);
            dsu.unite(x, y);
        }
    }

    return result;
}
