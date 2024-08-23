// 無向グラフの閉路検出: union-find
// NOTE: オンラインジャッジに通してない
#include <bits/stdc++.h>
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


int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<bool> seen(n);
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        seen[i] = true;
        for (auto adj : G[i]) {
            if (seen[adj]) continue;
            if (!uf.unite(i, adj)) {
                // サイクル検知
                cout << 1 << endl;
                return 0;
            }
            seen[adj] = true;
        }
    }
    cout << 0 << endl;
}
