
#include "boruvki.h"

#include <algorithm>
#include <vector>

#include "dsu.h"
#include "edge_list.h"

constexpr int kInf = int(1e9);

EdgeList* Boruvki::getSpaingTree(EdgeList& graph) {
    struct edge {
        int u, v, w;
    };

    const edge_list_t& graph_struct = (*graph.getStructPointer());
    const int vertices_count = graph.getVerticesCount();
    const int edges_count = graph.getEdgesCount();
    EdgeList* result = new EdgeList(vertices_count, false, true);

    std::vector<edge> edges;
    edges.reserve(edges_count);
    std::for_each(graph_struct.begin(), graph_struct.end(), [&edges](auto& e) {
        edges.push_back({e.first.first, e.first.second, e.second});
    });

    DSU dsu(vertices_count);
    std::vector<int> cheapest(vertices_count + 1, -1);
    int num_trees = vertices_count;
    int mst_weight = 0;

    while (num_trees > 1) {
        for (int i = 0; i < vertices_count + 1; ++i) {
            cheapest[i] = -1;
        }

        for (size_t i = 0; i < edges.size(); ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;

            int src = dsu.find(u);
            int dst = dsu.find(v);

            if (src != dst) {
                if (cheapest[src] == -1 || edges[cheapest[src]].w >= w)
                    cheapest[src] = i;

                if (cheapest[dst] == -1 || edges[cheapest[dst]].w >= w)
                    cheapest[dst] = i;
            }
        }

        for (int i = 1; i < vertices_count + 1; ++i) {
            if (cheapest[i] != -1) {
                int src = dsu.find(edges[cheapest[i]].u);
                int dst = dsu.find(edges[cheapest[i]].v);

                if (src != dst) {
                    edge& res = edges[cheapest[i]];
                    result->addEdge(res.u + 1, res.v + 1, res.w);
                    mst_weight += res.w;
                    dsu.unite(src, dst);
                    --num_trees;
                }
            }
        }
    }

    return result;
}
