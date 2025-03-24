#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ジャンル
// ゲーム問題, グラフ理論
// 頂点数の制約が小さいので全探索を視野に入れる
// => 偶数路は全列挙できる
// => ゲーム問題はdpが多いがそれをするまでもない

// ポイント
// 奇閉路を持たない => 二部グラフ
// => グラフ問題はまずなんらかの特殊グラフでないかをよく考える
// 01反転は^を使う

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    set<P> path;
    auto dfs = [&](auto dfs, int s, int v, int p, int d) -> void {
        if (s != p && d % 2 == 1) {
            path.emplace(min(s, v), max(s, v));
        }
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, s, u, v, d + 1);
        }
    };

    rep(i, n) dfs(dfs, i, i, -1, 0);

    if (path.size() % 2 == 0) {
        cout << "Second" << endl;
    } else {
        cout << "First" << endl;
        auto it = path.begin();
        cout << it->first + 1 << ' ' << it->second + 1 << endl;
        path.erase(it);
    }

    while (true) {
        int u, v; cin >> u >> v;
        if (u == -1 && v == -1) break;
        u--, v--;
        path.erase({u, v});
        auto it = path.begin();
        cout << it->first + 1 << ' ' << it->second + 1 << endl;
        path.erase(it);
    }
}

// 二部グラフであることを利用した解法
int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<P> es(n - 1);
    rep(i, n - 1) {
        int u, v; cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        es[i] = {u, v};
    }

    vector<vector<int>> group(2);
    auto dfs = [&](auto dfs, int v, int p, int c) -> void {
        group[c].push_back(v);
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v, c^1);
        }
    };
    dfs(dfs, 0, -1, 0);

    // 別グループの頂点間エッジは二部性を崩さない
    set<P> st;
    for (auto u : group[0]) {
        for (auto v : group[1]) {
            st.emplace(min(u, v), max(u, v));
        }
    }
    rep(i, n - 1) st.erase(es[i]);

    if (st.size() % 2 == 0) {
        cout << "Second" << endl;
    } else {
        cout << "First" << endl;
        auto it = st.begin();
        cout << it->first + 1 << ' ' << it->second + 1 << endl;
        st.erase(it);
    }

    while (true) {
        int u, v; cin >> u >> v;
        if (u == -1 && v == -1) break;
        u--, v--;
        st.erase({u, v});
        auto it = st.begin();
        cout << it->first + 1 << ' ' << it->second + 1 << endl;
        st.erase(it);
    }
}
