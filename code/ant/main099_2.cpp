// 最小費用流: p199
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// プライマル・デュアル法による解法（ポテンシャルつきダイクストラ）
// 「残余グラフにおける最短路を探索 -> 目一杯流す -> 残余グラフの更新」を繰り返すのは同じ
// 最短路探索がベルマンフォードだとO(EV)かかるので、うまいこと重みを非負にしてダイクストラ使うことでO(ElogV)にしてO(FElogV)でやろうという発想
// ポテンシャルは仮想の高さを全てに加えるイメージ。重みの大小関係は変えないように底上げをする。

// ポテンシャルhiについて
// fi+1を求めるには、fiの最短路を求める必要があるが、これにはhiが必要。しかしhiを求めるのにfiの最短路を求める必要があり矛盾が生じる（循環してしまう）。
// しかしfiの残余グラフのエッジはhi-1を使うことで非負にできるため、fi + hi-1によりダイクストラを実行できる。
// つまり`fi + hi-1 = fi+1 + hi`が成立する。
// hi-1がfiを非負にできるのは、fiの残余グラフに存在するエッジが、
//   (1)fi-1の残余グラフにも含まれるなら非負が保証されるし
//   (2)fi-1の残余グラフに含まれないなら、fi-1の逆辺に流れたということであり、その逆辺は非負なので元の順辺とともに非負になるには0しかない
// 初回(i=0)に限りh0は求めておく必要がある。初回はf0 + h0 = f1 + h0'になる。h0をベルマンフォード使っているならh0 = h0'になるし、
// h0=0としているならh0≠h0'だが、h0'をh0として最初の計算を行なっても結果は同じになる。
// 以降はf1 + h0 = h2 + h1という漸化式が成立する。

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {};
};

const int INF = 1e8; // 最大距離
int n;
vector<vector<Edge>> G;
vector<int> dist, prevv, preve, h;  // h: ポテンシャル

void addEdge(int from, int to, int cap, int cost) {
    G[from].emplace_back(to, cap, cost, G[to].size());
    G[to].emplace_back(from, 0, -cost, G[from].size() - 1);  // 逆辺
}

int minCostFlow(int s, int t, int f) {
    int res = 0;
    while (f > 0) {
        // ダイクストラ法でs-tの最短路を求める
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
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];  // ポテンシャル項`h[v]- h[e.to]`を加える
                    // 経路保存
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    pq.emplace(dist[e.to], e.to);
                }
            }
        }

        // 現在の残余グラフでsからtへ辿り着けない、つまりこれ以上フローを増やせない
        if (dist[t] == INF) return -1;

        // ポテンシャルの更新
        for (int i = 0; i < n; i++) h[i] += dist[i];

        // s-tの最短路に目一杯流す
        // 保存しておいた最短路を逆順に辿りつつ最小容量を求める
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
    int m, s, t, f; cin >> n >> m >> s >> t >> f;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, cap, cost; cin >> from >> to >> cap >> cost;
        addEdge(from, to, cap, cost);
    }

    dist = prevv = preve = h = vector<int>(n);
    cout << minCostFlow(s, t, f) << endl;
}
