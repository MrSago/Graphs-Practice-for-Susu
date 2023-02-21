
#include "prim.h"

#include <map>
#include <set>
#include <vector>

#include "adj_matrix.h"
#include "edge_list.h"

constexpr int kInf = int(1e9);

EdgeList* Prim::getSpaingTreeDenseGraph(AdjacencyMatrix* graph) {
    auto matrix = graph->getGraphPointer();
    std::map<std::pair<int, int>, int> result;
    std::vector<bool> used_vertices(matrix->size());
    std::vector<int> min_edges(matrix->size(), kInf);
    std::vector<int> selected_edges(matrix->size(), -1);

    min_edges[0] = 0;
    for (int i = 0; i < matrix->size(); ++i) {
        int v = -1;

        for (int j = 0; j < matrix->size(); ++j) {
            if (!used_vertices[j] && (v == -1 || min_edges[j] < min_edges[v])) {
                v = j;
            }
        }

        if (min_edges[v] == kInf) {
            exit(0);
        }

        used_vertices[v] = true;
        if (selected_edges[v] != -1) {
            result[{v, selected_edges[v]}] = min_edges[v];
            result[{selected_edges[v], v}] = min_edges[v];
        }

        for (int to = 0; to < matrix->size(); ++to) {
            if ((*matrix)[v][to] < min_edges[to]) {
                min_edges[to] = (*matrix)[v][to];
                selected_edges[to] = v;
            }
        }
    }

    return new EdgeList(std::move(result), false, true, matrix->size());
}

EdgeList* Prim::getSpaingTreeSparseGraph(AdjacencyList* graph) {
    auto list = graph->getGraphPointer();
    std::map<std::pair<int, int>, int> result;
    std::vector<int> min_edges(list->size(), kInf);
    std::vector<int> selected_edges(list->size(), -1);

    std::set<std::pair<int, int> > q;
    q.insert({0, 0});

    min_edges[0] = 0;
    for (int i = 0; i < list->size(); ++i) {
        if (q.empty()) {
            exit(0);
        }

        int v = q.begin()->second;
        q.erase(q.begin());

        if (selected_edges[v] != -1) {
            result[{v, selected_edges[v]}] = min_edges[v];
            result[{selected_edges[v], v}] = min_edges[v];
            min_edges[v] = 0;
        }

        for (size_t j = 0; j < (*list)[v].size(); ++j) {
            int to = (*list)[v][j].first;
            int weight = (*list)[v][j].second;
            if (weight < min_edges[to]) {
                q.erase({min_edges[to], to});
                min_edges[to] = weight;
                selected_edges[to] = v;
                q.insert({min_edges[to], to});
            }
        }
    }

    return new EdgeList(std::move(result), false, true, list->size());
}
