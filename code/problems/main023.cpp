// E - Minimize Sum of Distances
// https://atcoder.jp/contests/abc348/tasks/abc348_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 木は本質的にdp的性質を持っている。よってd(x,i)を考える時にN回計算するのではなく、
// 差分に注目した効率化ができないかを考えるのが自然。差分を考えると小さい部分木への移動を繰り返せばいいことに気づけ、
// 重心の問題に帰着することがわかる
// "木"や"min"などあるあるな条件の時は、図形的性質を確認しておく

int n;
ll total = 0;
vector<vector<int>> G;
vector<int> c, centroids;
vector<ll> dp;

void getCentroids(int v, int p) {
    dp[v] = c[v];
    bool is_centroid = true;
    for (auto ch : G[v]) {
        if (ch == p) continue;
        getCentroids(ch, v);
        if (dp[ch] > total / 2) is_centroid = false;
        dp[v] += dp[ch];
    }
    if (total - dp[v] > total / 2) is_centroid = false;
    if (is_centroid) centroids.push_back(v);
}

void dfs(ll& ans, int v, int p, int d) {
    ans += ll(d) * c[v];
    for (auto ch : G[v]) {
        if (ch == p) continue;
        dfs(ans, ch, v, d + 1);
    }
}

int main() {
    cin >> n;
    G = vector<vector<int>>(n, vector<int>());
    c = vector<int>(n);
    dp = vector<ll>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        total += c[i];
    }

    getCentroids(0, -1);

    ll ans = 0;
    dfs(ans, centroids[0], -1, 0);
    cout << ans << endl;
}
