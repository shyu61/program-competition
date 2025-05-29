#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// トポロジカルソート
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja

// 🔷抑えるべき抽象論は？
// bfs
// - 入次数が0であることを利用する
// - 入次数が0のノードを見終わったらedgeを削除して繰り返し見ていく
// dfs
// - 帰りがけ順に見ると、始点が異なるdfsの結果を結合できることを利用する

// 🔷類問を考える
// LCAをrmqで求める方法では、dfsの行きがけ順を利用する

// bfsによる解法
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        deg[v]++;
    }

    queue<int> que;
    rep(i, n) {
        if (deg[i] == 0) que.push(i);
    }

    vector<int> ans;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        ans.push_back(v);

        for (auto u : g[v]) {
            deg[u]--;
            if (deg[u] == 0) que.push(u);
        }
    }

    for (auto v : ans) cout << v << '\n';
}

// dfsによる解法
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    vector<int> ans;
    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v) -> void {
        seen[v] = true;
        for (auto u : g[v]) {
            if (!seen[u]) dfs(dfs, u);
        }
        ans.push_back(v);
    };
    rep(i, n) {
        if (!seen[i]) dfs(dfs, i);
    }
    reverse(ans.begin(), ans.end());
    rep(i, n) cout << ans[i] << '\n';
}
