
#ifndef DSU_H
#define DSU_H

#include <vector>

class DSU {
   public:
    DSU(int n);
    int find(int x);
    void unite(int x, int y);

   private:
    std::vector<int> parent_;
    std::vector<int> rank_;
};

#endif  // DSU_H
