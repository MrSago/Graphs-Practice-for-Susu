
#include "DSU.hpp"

#include <numeric>

DSU::DSU(int N) : parent(N), rank(N, 0) {
    std::iota(parent.begin(), parent.end(), 0);
}

int DSU::find(int x) {
    return x == parent[x] ? x : (parent[x] = find(parent[x]));
}

void DSU::unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (rank[x] < rank[y]) {
            std::swap(x, y);
        }
        parent[y] = x;
        if (rank[x] == rank[y]) {
            ++rank[x];
        }
    }
}
