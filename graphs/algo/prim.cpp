
#include "prim.hpp"

EdgeList* Prim::getSpaingTreeDenseGraph(AdjacencyMatrix* adjMatrix) {
    auto matrix = adjMatrix->getGraphPointer();
    std::map<std::pair<int, int>, int> tree;
    std::vector<bool> used(matrix->size());
    std::vector<int> min_e(matrix->size(), INF);
    std::vector<int> sel_e(matrix->size(), -1);

    min_e[0] = 0;
    for (int i = 0; i < matrix->size(); ++i) {
        int v = -1;

        for (int j = 0; j < matrix->size(); ++j) {
            if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
                v = j;
            }
        }

        if (min_e[v] == INF) {
            exit(0);
        }

        used[v] = true;
        if (sel_e[v] != -1) {
            tree[{v, sel_e[v]}] = min_e[v];
            tree[{sel_e[v], v}] = min_e[v];
        }

        for (int to = 0; to < matrix->size(); ++to) {
            if ((*matrix)[v][to] < min_e[to]) {
                min_e[to] = (*matrix)[v][to];
                sel_e[to] = v;
            }
        }
    }

    return new EdgeList(std::move(tree), false, true, matrix->size());
}

EdgeList* Prim::getSpaingTreeSparseGraph(AdjacencyList* adjList) {
    auto list = adjList->getGraphPointer();
    std::map<std::pair<int, int>, int> tree;
    std::vector<int> min_e(list->size(), INF);
    std::vector<int> sel_e(list->size(), -1);

    std::set<std::pair<int, int> > q;
    q.insert({0, 0});

    min_e[0] = 0;
    for (int i = 0; i < list->size(); ++i) {
        if (q.empty()) {
            exit(0);
        }

        int v = q.begin()->second;
        q.erase(q.begin());

        if (sel_e[v] != -1) {
            tree[{v, sel_e[v]}] = min_e[v];
            tree[{sel_e[v], v}] = min_e[v];
            min_e[v] = 0;
        }

        for (size_t j = 0; j < (*list)[v].size(); ++j) {
            int to = (*list)[v][j].first;
            int weight = (*list)[v][j].second;
            if (weight < min_e[to]) {
                q.erase({min_e[to], to});
                min_e[to] = weight;
                sel_e[to] = v;
                q.insert({min_e[to], to});
            }
        }
    }

    return new EdgeList(std::move(tree), false, true, list->size());
}
