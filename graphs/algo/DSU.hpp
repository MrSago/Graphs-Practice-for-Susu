
#ifndef DSU_HPP
#define DSU_HPP

#include <vector>

class DSU {
   public:
    DSU(int N);
    int find(int x);
    void unite(int x, int y);

   private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif  // DSU_HPP
