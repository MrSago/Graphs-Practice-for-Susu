
#include "kruscal.hpp"

#include <algorithm>

EdgeList* Kruscal::getSpaingTree(EdgeList* edgeList) {
    auto list = edgeList->getGraphPointer();
    int verticesCount = edgeList->getVerticesCount();
    int edgesCount = edgeList->getEdgesCount();

    std::vector<std::pair<int, std::pair<int, int>>> graph;
    graph.reserve(edgesCount);
    std::for_each(list->begin(), list->end(), [&graph](auto& edge) {
        graph.push_back({edge.second, {edge.first.first, edge.first.second}});
    });
    std::sort(graph.begin(), graph.end());

    std::map<std::pair<int, int>, int> result;
    DSU dsu(verticesCount);

    for (int i = 0; i < edgesCount; ++i) {
        int x = graph[i].second.first;
        int y = graph[i].second.second;
        int w = graph[i].first;
        if (dsu.find(x) != dsu.find(y)) {
            result[{x, y}] = w;
            result[{y, x}] = w;
            dsu.unite(x, y);
        }
    }

    return new EdgeList(std::move(result), false, true, verticesCount);
}
