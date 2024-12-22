// 応用問題(The Windy's): p218
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// おもちゃと工場の最適なマッチングを見つけつつ、その工場の中で何番目に作るかを求める問題
// 素直に考えると、2段階の割当を含む問題と言える
// コストを最小化する割当問題 -> 最小費用流を使って解きたい
// -> 選択肢
// 1. グラフを工夫して最小費用流が適用できる形にする
// 2. 2つの割当を直列に分けて解く
// 3. 全く違うアプローチ
// -> 2.はそれぞれが独立ではないので難易度高そう。一旦1.で考えてみる。
// -> 順番割当は、各時刻や順番ごとにノードを分けるのがセオリーなので、おもちゃの数だけ各工場を複製して考える
// -> 重みを考える。素直に前から見ると、自身の重みは、自分より前に作られたおもちゃの重みの合計に依存し静的に決められない。
// -> 静的に重みを決められないと解けない、なんとかして静的に重みを決められないか？
// -> 累積構造を持っている場合、前から考えてダメなら後ろから考えてみる
// -> 自身の重みは、`重み*後ろから何番目か`で表現でき、静的に決められることがわかる
// -> ただの最小費用流に帰着できた。

// 抽象化
// 累積構造や漸化式構造を持っている場合、前から考えてダメなら後ろから考えてみる。
// DPでもdpテーブルを後ろから埋める場合があるのと同じ

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 1e5 + 1;
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
    int p; cin >> p;
    while (p--) {
        int N, M; cin >> N >> M;
        vector<vector<int>> Z(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> Z[i][j];
            }
        }

        int s = N + N * M, t = s + 1;
        V = t + 1;
        G = vector<vector<Edge>>(V);
        for (int i = 0; i < N; i++) addEdge(s, i, 1, 0);
        for (int i = 0; i < N * M; i++) addEdge(N + i, t, 1, 0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N * M; j++) {
                addEdge(i, N + j, 1, Z[i][j / N] * (j % N + 1));
            }
        }

        cout << fixed << setprecision(6) << double(minCostFlow(s, t, N)) / N << endl;
    }
}
