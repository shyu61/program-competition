// ビットDP(巡回セールスマン問題): p173
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// bitDPはメモ化再帰の方が考えやすい
// 特に"遷移の方向"を意識すると良い

struct Edge {
    int to; int w;
    Edge(int to, int w) : to(to), w(w) {};
};

const int INF = 15001;
int n;
vector<vector<Edge>> G;
vector<vector<int>> dp;

int f(int S, int v) {
    if (dp[S][v] >= 0) return dp[S][v];
    if (S == (1 << n) - 1 && v == 0) return dp[S][v] = 0;

    int res = INF;
    for (auto [u, w] : G[v]) {
        if (!(S >> u & 1)) {
            res = min(res, f(S | 1 << u, u) + w);
        }
    }
    return dp[S][v] = res;
}

int main() {
    int m; cin >> n >> m;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, w; cin >> from >> to >> w;
        G[from].emplace_back(to, w);
    }

    // dp[S][v]: 訪問済みの頂点集合S, 現在の頂点vの状態で残りの頂点全てを訪問して0に帰ってくる最小値
    dp = vector<vector<int>>(1 << n, vector<int>(n, -1));
    f(0, 0);

    cout << dp[0][0] << endl;
}
