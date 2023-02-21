
#include "DSU.h"

#include <numeric>
#include <vector>

DSU::DSU(int n) : parent_(n), rank_(n, 0) {
    std::iota(parent_.begin(), parent_.end(), 0);
}

int DSU::find(int x) {
    return x == parent_[x] ? x : (parent_[x] = find(parent_[x]));
}

void DSU::unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (rank_[x] < rank_[y]) {
            std::swap(x, y);
        }
        parent_[y] = x;
        if (rank_[x] == rank_[y]) {
            ++rank_[x];
        }
    }
}
