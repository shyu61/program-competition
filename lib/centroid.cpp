#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> G;
// 頂点vを根とする部分木のサイズ
vector<int> dp, centroids;

void dfs(int v, int p) {
    dp[v] = 1;
    bool is_centroid = true;
    for (auto u : G[v]) {
        if (u == p) continue;
        dfs(u, v);
        // 頂点vを削除してできる部分木のサイズを確認
        if (dp[u] > n / 2) is_centroid = false;
        dp[v] += dp[u];
    }
    // 頂点vを削除してできる逆側の部分木のサイズを確認
    if (n - dp[v] > n / 2) is_centroid = false;
    if (is_centroid) centroids.push_back(v);
}

int main () {
    cin >> n;
    G = vector<vector<int>>(n, vector<int>());
    dp = vector<int>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 適当な頂点を根とする
    dfs(0, -1);

    cout << "重心の個数: " << centroids.size() << endl;
    if (centroids.size() > 0) {
        for (auto v : centroids) cout << v << " ";
        cout << endl;
    }
}
