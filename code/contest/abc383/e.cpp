#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
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
    int N, M, K; cin >> N >> M >> K;
    vector<tuple<int, int, int>> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {w, --u, --v};
    }
    vector<int> A(N), B(N);
    for (int i = 0; i < K; i++) {
        int a; cin >> a;
        A[--a]++;
    }
    for (int i = 0; i < K; i++) {
        int b; cin >> b;
        B[--b]++;
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    ll ans = 0;
    for (auto [c, u, v] : edges) {
        if (uf.same(u, v)) continue;
        u = uf.root(u);
        v = uf.root(v);
        if (A[v]) swap(u, v);
        if (A[u] && B[v]) {
            // 作れるだけペアを作る
            int x = min(A[u], B[v]);
            ans += ll(c) * x;
            A[u] -= x; B[v] -= x;
        }
        uf.unite(u, v);
        A[uf.root(u)] = A[u] + A[v];
        B[uf.root(u)] = B[u] + B[v];
    }
    cout << ans << endl;
}
