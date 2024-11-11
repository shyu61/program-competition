// 応用問題(Intervals): p220
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 分からない時はまず特定の簡単な条件で考えてみる。例えばk=1の場合を見ると、有名問題である重み付き区間スケジューリング問題になる
// そもそも明らかに組合せ最適化問題であり、直前までで何を選んだかに依存して次の区間の選択を決定できるので、漸化式でモデリングできることは直感的にわかる
// -> DPを考えるとk=1の場合はdpで解けることがわかる(有名問題だし知っておくべきでもある)
// -> これをk>1に拡張する方法を考える
// -> DPは範囲制約が苦手。そもそもDPは工夫により遷移がシンプルに記述できることが全体。範囲制約は遷移パターンが多く指数的に増え管理しきれなくなる。
// -> 範囲制約はネットワークフローが得意。DPはDAGの最短路としての側面を持ち、グラフとの相性が良い。グラフの方が表現力が高く、範囲制約は容量制約としてネットワークフローで表現できる。

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 1e8;
int V;
vector<vector<Edge>> G;

void addEdge(int from, int to, int cap, int cost) {
    G[from].emplace_back(to, cap, cost, G[to].size());
    G[to].emplace_back(from, 0, -cost, G[from].size() - 1);
}

int minCostFlow(int s, int t, int f) {
    vector<int> dist(V), prevv(V), preve(V), h(V);
    int res = 0;
    while (f > 0) {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [w, v] = pq.top(); pq.pop();
            if (w > dist[v]) continue;

            for (int i = 0; i < G[v].size(); i++) {
                Edge e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    pq.emplace(dist[e.to], e.to);
                }
            }
        }
        // 現在の残余グラフでsからtへ辿り着けない、つまりこれ以上フローを増やせない
        if (dist[t] == INF) return -1;
        // ポテンシャルの更新
        for (int i = 0; i < V; i++) h[i] += dist[i];
        // s-tの最短路に目一杯流す
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        // 残余グラフの更新
        for (int v = t; v != s; v = prevv[v]) {
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

int main() {
    int N, K; cin >> N >> K;
    vector<int> a(N), b(N), w(N), x(N * 2);
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i] >> w[i];
        x[i * 2] = a[i];
        x[i * 2 + 1] = b[i];
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());

    int m = x.size();
    int s = m, t = s + 1;
    V = t + 1;

    G = vector<vector<Edge>>(V);
    int res = 0;
    addEdge(s, 0, K, 0);
    addEdge(m - 1, t, K, 0);
    for (int i = 0; i < m - 1; i++) addEdge(i, i + 1, INF, 0);  // i+1を使わない場合: dp[i+1] = dp[i];
    for (int i = 0; i < N; i++) {
        int u = find(x.begin(), x.end(), a[i]) - x.begin();
        int v = find(x.begin(), x.end(), b[i]) - x.begin();
        // u->vへcap=1,cost=-w[i]の辺を張る
        // 負の重みを工夫して全て非負にする
        addEdge(v, u, 1, w[i]);  // あらかじめu->vに目一杯流す、つまり残余グラフは逆辺のみになる
        addEdge(s, v, 1, 0);
        addEdge(u, t, 1, 0);
        res -= w[i];
    }

    res += minCostFlow(s, t, K + N);
    cout << -res << endl;
}

// k=1の場合
// struct Section {
//     int a, b, w;
//     Section() {};
//     Section(int a, int b, int w) : a(a), b(b), w(w) {};
//     bool operator<(const Section &other) const { return b < other.b; };
// };

// int main() {
//     int N, K; cin >> N >> K;
//     vector<Section> c(N);
//     for (int i = 0; i < N; i++) {
//         int a, b, w; cin >> a >> b >> w;
//         c[i] = Section(a, b, w);
//     }

//     sort(c.begin(), c.end());

//     vector<int> dp(N);
//     dp[0] = c[0].w;
//     for (int i = 1; i < N; i++) {
//         // i番目のタスクと重ならない最後のタスクの探索
//         int p = i - 1;
//         while (p >= 0 && c[p].b > c[i].a) p--;
//         if (p == -1) dp[i] = max(dp[i - 1], c[i].w);
//         else dp[i] = max(dp[i - 1], dp[p] + c[i].w);
//     }
//     cout << dp[N - 1] << endl;
// }
