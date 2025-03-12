#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
using TP = tuple<int, int, int>;

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) {
        return -parents[leader(x)];
    }

    vector<vector<int>> groups() {
        vector<int> lds(_n);
        for (int i = 0; i < _n; i++) lds[i] = leader(i);
        vector<vector<int>> res(_n);
        for (int i = 0; i < _n; i++) res[lds[i]].push_back(i);
        res.erase(
            remove_if(
                res.begin(),
                res.end(),
                [&](const vector<int>& vec) { return vec.empty(); }
            ),
            res.end()
        );
        return res;
    }
};

ll pow(ll x, ll n, ll mod = 1) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n; ll k; cin >> n >> k;
    vector<int> p(n);
    rep(i, n) cin >> p[i], p[i]--;

    UnionFind uf(n);
    rep(i, n) uf.merge(i, p[i]);

    vector<TP> dist(n, {-1, -1, -1});
    auto dfs = [&](auto dfs, int v) -> TP {
        if (get<0>(dist[v]) != -1) return dist[v];
        auto [d, t, i] = dfs(dfs, p[v]);
        return dist[v] = {d, t + 1, i};
    };

    vector<int> ans(n), id(n, -1);
    auto get_cycle = [&](int s, vector<int>& cyc) -> int {
        int d = 0;
        while (id[s] == -1) {
            id[s] = d++;
            s = p[s];
        }
        int len = d - id[s];
        rep(i, len) {
            cyc.push_back(s);
            dist[s] = {0, s, i};
            s = p[s];
        }
        return cyc.size();
    };

    // 連結成分ごとに処理
    for (auto& group : uf.groups()) {
        vector<int> cyc;
        int r = get_cycle(group[0], cyc);
        ll nk = pow(2, k, r);

        // 閉路までの距離を計算
        for (auto v : group) {
            if (get<0>(dist[v]) == -1) dfs(dfs, v);
        }

        for (auto v : group) {
            auto [d, t, i] = dist[v];
            // 閉路まで辿り着かない場合
            if (int(log2(d)) + 1 > k) {
                int step = 1;
                rep(i, k) step *= 2;
                // 頂点vからstep回進んだ先の頂点
                int cur = v;
                rep(i, step) cur = p[cur];
                ans[v] = cur;
            }

            int step = nk - d % r;
            if (step < 0) step += r;

            ans[v] = cyc[(i + step) % r];
        }
    }

    rep(i, n) cout << ans[i] + 1 << ' ';
    cout << endl;
}
