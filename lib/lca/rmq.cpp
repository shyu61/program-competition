#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

// 根付き木を扱う問題はグラフを根からDFSし、その順に番号を付けて一列に並べて扱うとうまくいくことがよくある
// => 木を区間として扱えるので、seg木と相性が良い
//   例) 部分木をその最上位ノードvとして[v[in],v[out]]の区間として表現できる
//   例) LCAはその逆で、u,vの訪問番号に挟まれる位置に部分木の根があることを利用している

template<auto op, int iv>
struct Segtree {
private:
    int n = 1;
    vector<P> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<P>(n * 2 - 1, {iv, -1});

        for (int i = 0; i < sz; i++) dat[i + n - 1] = {a[i], i};
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    P query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return {iv, -1};
        if (a <= l && r <= b) return dat[id];
        else {
            P vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            P vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }
};

P op(P a, P b) { return min(a, b); }

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n) {
        int k; cin >> k;
        rep(j, k) {
            int u; cin >> u;
            g[i].push_back(u);
            g[u].push_back(i);
        }
    }

    // vs: 訪問順, depth: 深さ, id: その頂点の初回訪問番号
    vector<int> vs(n * 2 - 1), depth(n * 2 - 1), id(n);
    auto dfs = [&](auto dfs, int& k, int v, int p = -1, int d = 0) -> void {
        id[v] = k;
        vs[k] = v;
        depth[k++] = d;
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, k, u, v, d + 1);
            vs[k] = v;
            depth[k++] = d;
        }
    };
    {
        int k = 0;
        dfs(dfs, k, 0);
    }

    Segtree<op, INF> rmq(depth);
    auto lca = [&](int u, int v) -> int {
        int k = rmq.query(min(id[u], id[v]), max(id[u], id[v]) + 1).second;
        return vs[k];
    };

    int u, v; cin >> u >> v;
    cout << lca(u, v) << endl;
}
