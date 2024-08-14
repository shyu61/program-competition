#include <vector>
using namespace std;

struct UnionFind {
    // 親のインデックスを保持する
    // rootは負の値を取り、その絶対値がその木における要素数を表す
    vector<int> par;

    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }

    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);  // 経路圧縮
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        // 常に小さい木を大きい木に結合する
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }
};