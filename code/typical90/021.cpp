#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 方針
// 強連結成分分解をする -> Σci(ci-1)/2

struct Scc {
    int n;
    vector<bool> used;
    vector<int> vs, cmp;
    vector<vector<int>> g, rg;
    Scc(int _n, const vector<vector<int>>& _g, const vector<vector<int>>& _rg)
    : n(_n), g(_g), rg(_rg) {
        used.resize(n);
        cmp.resize(n);
    }

    void dfs(int v) {
        used[v] = true;
        for (auto u : g[v]) {
            if (!used[u]) dfs(u);
        }
        vs.push_back(v);
    }

    void rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (auto u : rg[v]) {
            if (!used[u]) rdfs(u, k);
        }
    }

    int decompose() {
        fill(used.begin(), used.end(), 0);
        rep(i, n) {
            if (!used[i]) dfs(i);  // vsを計算
        }
        fill(used.begin(), used.end(), 0);
        int k = 0;
        // 帰りがけに振った番号が大きいもの(根本側)から調べる
        for (int i = n - 1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), rg(n);
    rep(i, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    Scc scc(n, g, rg);
    int k = scc.decompose();

    vector<int> cnt(k);
    rep(i, n) cnt[scc.cmp[i]]++;

    ll ans = 0;
    rep(i, k) {
        ll x = cnt[i];
        ans += x * (x - 1) / 2;
    }
    cout << ans << endl;
}
