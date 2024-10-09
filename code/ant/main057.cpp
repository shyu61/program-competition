// 最短路問題(ベルマンフォード法): p95
#include <bits/stdc++.h>
using namespace std;

// ベルマンフォード法: 計算量がO(VE)でダイクストラより不利だが負の重みにも適用でき、負のサイクル検出にも使える
// グラフが閉路を持たないDAGとかならDPなのでトポロジカル順に更新すればO(E)で処理できる
// 閉路がある場合は、1回の緩和操作で経路が短い方から少なくとも1つは最短経路が確定することを利用して、V-1回緩和操作を行う。
// (最短経路は最長のものでもV-1以下なので、V-1回緩和すればすべての最短経路が確定する)
// 貪欲法であるダイクストラと比較して、全探索的な手法と言える

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 1e9 + 1;
int n, m, s;
vector<vector<Edge>> G;
vector<int> d;

void bellmanFord() {
    while (1) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            for (auto adj : G[i]) {
                if (d[i] != INF && d[adj.to] > d[i] + adj.cost) {
                    d[adj.to] = d[i] + adj.cost;
                    update = true;
                }
            }
        }
        // 最大でもV-1回まわればいづれのdも更新はされなくなる
        if (!update) break;
    }
}

int main() {
    cin >> n >> m >> s;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        G[u].emplace_back(v, cost);
    }

    d = vector<int>(n, INF);
    d[s] = 0;
    bellmanFord();

    for (int i = 0; i < n; i++) {
        if (d[i] == INF) cout << "INF" << endl;
        else cout << d[i] << endl;
    }
}
