#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// - 無向グラフ, 数列, 数式問題, 組み合わせ最適化, マッチング問題, パス最適化, 最大重みの最小化

// 方針
// グラフにおける最大重みの最小化とくれば、MST一択
// MSTの構築過程は最大重みの最小化そのものなので、kruskal法を使いつつ、ペアリングしていくことを考える

// 別の観点から見ると、数式問題なので(1)構成要素の解析と(2)数式の目的を考えるのも定石。(2)より組合せ最適化問題であることがわかる。
// 組合せ最適化なので、全探索,貪欲法,dpあたりを検討する。全探索は明らかに無理で、dpも遷移の記述が難しそうなので可能性低い。
// どちらにせよ「最小となる条件」をまず特定する必要があるので考える。明らかに最小のedgeのみで2点を結べる時に最小。この時点でedgeを基準に考えれば良いことがわかるし、まさにMSTだと気づけるはず。

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }
    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }
    bool same(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    int size(int x) { return -par[root(x)]; }
};

int main() {
    int N, M, K; cin >> N >> M >> K;
    vector<tuple<int, int, int>> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {w, --u, --v};
    }
    vector<int> A(N), B(N);
    for (int i = 0; i < K; i++) { int a; cin >> a; A[--a]++; }
    for (int i = 0; i < K; i++) { int b; cin >> b; B[--b]++; }

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
        // ペアを作った2頂点は縮約する(以降のループのedgeは必ず重みが大きくなるので、"パスの重み"は変更される)
        uf.unite(u, v);
        A[uf.root(u)] = A[u] + A[v];
        B[uf.root(u)] = B[u] + B[v];
    }
    cout << ans << endl;
}
