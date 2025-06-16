#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc166/tasks/abc166_c

// 🔷抑えるべき抽象論は？
// "隣接"を扱うということは、"エッジ"を見ることと同値
// - 故に隣接リストを頂点ごとに走査しても、計算量はO(M)
// グラフの頂点に情報を持たせる場合もある
// - 別配列で持つ or 頂点番号自体を利用する

// エッジを見る解法
int main() {
    int n, m; cin >> n >> m;
    vector<int> h(n);
    rep(i, n) cin >> h[i];
    vector<bool> a(n, true);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        if (h[u] == h[v]) {
            a[u] = a[v] = false;
            continue;
        }
        if (h[u] > h[v]) swap(u, v);
        a[u] = false;
    }

    int ans = 0;
    rep(i, n) if (a[i]) ans++;
    cout << ans << endl;
}

// 隣接リストを頂点ごとに走査する解法
int main() {
    int n, m; cin >> n >> m;
    vector<int> h(n);
    rep(i, n) cin >> h[i];
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 0;
    rep(i, n) {
        bool ok = true;
        for (auto v : g[i]) {
            if (h[i] <= h[v]) {
                ok = false;
                break;
            }
        }
        if (ok) ans++;
    }
    cout << ans << endl;
}
