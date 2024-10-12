#include <bits/stdc++.h>
using namespace std;

// 重みが小さいものから順に全てのedgeを見ていき、閉路を形成しない限りmstに加えていく
// 閉路を形成しないためにはfrom,toが同じ連結成分でないことが条件(!uf.same(from, to))

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

struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost): from(from), to(to), cost(cost) {};

    bool operator<(const Edge& other) const {
        return cost < other.cost;
    };
};

const int INF = 1e9 + 1;
int n;
vector<Edge> E;
vector<int> d;

int kruskal() {
    int total = 0;

    // O(ElogE)
    sort(E.begin(), E.end());
    UnionFind uf(n);

    for (auto e : E) {
        if (uf.same(e.from, e.to)) continue;
        uf.unite(e.from, e.to);
        total += e.cost;
    }
    return total;
}
