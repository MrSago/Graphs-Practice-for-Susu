
#include "prim.h"

#include <map>
#include <set>
#include <vector>

#include "adj_matrix.h"
#include "edge_list.h"

constexpr int kInf = int(1e9);

EdgeList* Prim::getSpaingTreeDenseGraph(AdjacencyMatrix& graph) {
    const adj_matrix_t& matrix = (*graph.getStructPointer());
    const int vertices_count = graph.getVerticesCount();
    EdgeList* result = new EdgeList(false, true, vertices_count);
    std::vector<bool> used_vertices(vertices_count, false);
    std::vector<int> min_edges(vertices_count, kInf);
    std::vector<int> selected_edges(vertices_count, -1);

    min_edges[0] = 0;
    for (int i = 0; i < vertices_count; ++i) {
        int v = -1;

        for (int j = 0; j < vertices_count; ++j) {
            if (!used_vertices[j] && (v == -1 || min_edges[j] < min_edges[v])) {
                v = j;
            }
        }

        if (min_edges[v] == kInf) {
            exit(0);
        }

        used_vertices[v] = true;
        if (selected_edges[v] != -1) {
            result->addEdge(v, selected_edges[v], min_edges[v]);
        }

        for (int to = 0; to < vertices_count; ++to) {
            if (matrix[v][to] < min_edges[to]) {
                min_edges[to] = matrix[v][to];
                selected_edges[to] = v;
            }
        }
    }

    return result;
}

EdgeList* Prim::getSpaingTreeSparseGraph(AdjacencyList& graph) {
    const adj_list_t& list = (*graph.getStructPointer());
    const int vertices_count = graph.getVerticesCount();
    EdgeList* result = new EdgeList(false, true, vertices_count);
    std::vector<int> min_edges(vertices_count, kInf);
    std::vector<int> selected_edges(vertices_count, -1);

    std::set<std::pair<int, int> > q;
    q.insert({0, 0});

    min_edges[0] = 0;
    for (int i = 0; i < vertices_count; ++i) {
        if (q.empty()) {
            exit(0);
        }

        int v = q.begin()->second;
        q.erase(q.begin());

        if (selected_edges[v] != -1) {
            result->addEdge(v, selected_edges[v], min_edges[v]);
            min_edges[v] = 0;
        }

        for (size_t j = 0; j < list[v].size(); ++j) {
            int to = list[v][j].first;
            int weight = list[v][j].second;
            if (weight < min_edges[to]) {
                q.erase({min_edges[to], to});
                min_edges[to] = weight;
                selected_edges[to] = v;
                q.insert({min_edges[to], to});
            }
        }
    }

    return result;
}
