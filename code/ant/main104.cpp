// 応用問題(Farm Tour): p214
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最短路問題 -> 全探索,グラフ,DP -> 全探索はM!なので無理、DPはbitDPする必要があるが、状態数が2^M*Nなので無理、ダイクストラの複数回適用はうまくいかない
// -> 最短路を最小費用流と置き換えて解く -> 「往復」をs->tへの異なる2つのルートと読み替える

// ポイント
// - 最小費用流は容量1にすることで最短路問題に適用できる。これは最小費用流のアルゴリズムが内部で最短路探索を行なっているので全く同義になる
//   容量1のまま流量だけ1より大きくすることで複数経路探索になる
// - 「往復で別々の道」という制約を「s->tへの別の2つのルート」と読み替える
// 蟻の問題で衝突をすれ違いと読み替えるなど、構造的な変換の発想は超重要。思いつく鍵は、詰まった時に目的と制約、条件を「一度抽象化して視点を上げ、そこから別の具体的解釈を探る」こと。
// 目的や条件は基本具体で与えられるので、そのままでは発想を転換しにくい。一段抽象化してみてから、別の具体に落とせないか探りつつ視点を変えることが重要

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 35000 * 10000 + 1; // 最大距離
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
    int N, M; cin >> N >> M;
    G = vector<vector<Edge>>(N);
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        addEdge(a, b, 1, c);
        addEdge(b, a, 1, c);
    }

    V = N;
    cout << minCostFlow(0, N - 1, 2) << endl;
}
