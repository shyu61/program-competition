// 応用問題(Evacuation Plan): p215
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最も素直に最小費用流を使う解法

// 明らかにビルとシェルターの2つの割当問題。注意点は必ずしも1対1対応ではないこと。 -> マッチングではない
// -> 目的はコスト最小化 -> 普通に最小費用流が適用できる形にグラフを作れば解けそう
// 実際に各エッジを流れた量は逆辺のcapを見ればいい

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int MAX_D = 4 * 1000 * 100 + 1;
const int MAX_F = 1e5 + 1;
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
        fill(dist.begin(), dist.end(), MAX_D);
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
        if (dist[t] == MAX_D) return -1;
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
    vector<int> X(N), Y(N), B(N), P(M), Q(M), C(M);
    for (int i = 0; i < N; i++) cin >> X[i] >> Y[i] >> B[i];
    for (int i = 0; i < M; i++) cin >> P[i] >> Q[i] >> C[i];
    vector<vector<int>> E(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> E[i][j];
        }
    }

    int f = 0, cost = 0;

    V = N + M + 2;
    G = vector<vector<Edge>>(V);
    int s = N + M, t = s + 1;
    for (int i = 0; i < N; i++) {  // ビル->シェルター
        for (int j = 0; j < M; j++) {
            int d = abs(X[i] - P[j]) + abs(Y[i] - Q[j]) + 1;
            cost += E[i][j] * d;
            addEdge(i, N + j, MAX_F, d);
        }
    }
    for (int i = 0; i < N; i++) {
        f += B[i];
        addEdge(s, i, B[i], 0);  // s->ビル
    }
    for (int i = 0; i < M; i++) addEdge(N + i, t, C[i], 0);  // シェルター->t
    if (minCostFlow(s, t, f) < cost) {
        cout << "SUBOPTIMAL" << endl;
        // 実際の最適な計画を復元
        // 残余グラフに対して実際に流れた人数を出力
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << G[N + j][i].cap << (j == M - 1 ? "\n" : " ");
            }
        }
    } else {
        cout << "OPTIMAL" << endl;
    }
}
