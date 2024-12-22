// 木の直径: 全方位木dp
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> G;
vector<int> dp;
int dtr = 0;

void dfs1(int v, int par) {
    dp[v] = 0;
    for (auto [adj, cost] : G[v]) {
        if (adj == par) continue;
        dfs1(adj, v);
        dp[v] = max(dp[v], dp[adj] + cost);
    }
}

// val: par->vへ伝搬される値(parにおける最遠点までの距離)
void dfs2(int v, int par, int val) {
    vector<pair<int, int>> ch;
    ch.emplace_back(0, -1);
    // vの子の各部分木の中での最遠点までの距離をchに格納
    for (auto [adj, cost] : G[v]) {
        if (adj == par) ch.emplace_back(val + cost, par);
        else ch.emplace_back(dp[adj] + cost, adj);
    }
    sort(ch.rbegin(), ch.rend());
    // 直径を更新
    dtr = max(dtr, ch[0].first + ch[1].first);

    // 次の頂点へ移動
    for (auto [adj, cost] : G[v]) {
        if (adj == par) continue;
        if (adj == ch[0].second) dfs2(adj, v, ch[1].first);
        else dfs2(adj, v, ch[0].first);
    }
}

int main() {
    int n; cin >> n;
    G = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    dp = vector<int>(n);
    for (int i = 0; i < n - 1; i++) {
        int s, t, w; cin >> s >> t >> w;
        G[s].emplace_back(t, w);
        G[t].emplace_back(s, w);
    }

    dfs1(0, -1);
    dfs2(0, -1, 0);
    cout << dtr << endl;
}
