#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// 想定解
// 単なる最短路問題よりbfs

// 罠
// 「閉路」という単語から閉路検出を試みるとハマる

// ポイント
// 閉路の全探索はほぼ不可能: パス全探索と同じオーダーであり、O(n!)
// → 全探索するというアイディアは頂点制約が非常に小さい場合を除いて捨てる

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int a, b; cin >> a >> b, a--, b--;
        g[a].push_back(b);
    }

    int ans = INF;
    vector<int> dist(n, -1);
    auto bfs = [&](int v) -> bool {
        queue<int> que;
        que.push(v);
        dist[v] = 0;

        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto u : g[v]) {
                if (u == 0) {
                    cout << dist[v] + 1 << endl;
                    return true;
                }
                if (dist[u] != -1) continue;
                que.push(u);
                dist[u] = dist[v] + 1;
            }
        }
        return false;
    };

    if (!bfs(0)) cout << -1 << endl;
}
