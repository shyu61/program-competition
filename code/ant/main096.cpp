// 最小カット: p194
#include <bits/stdc++.h>
using namespace std;

// 最大フロー最小カット定理
// 1.上界の証明: カットの定義より最大フローは任意のカット容量以下でないといけない。ゆえに最大フロー<=最小カット
// 2.最大フローがあるカットと等しくなることの証明: 残余ネットワークにおいて、s->tの増加パスはないのでsから到達可能な頂点集合SとT=V\Sに分けることができ、S,Tはカットを形成する。
// このカット部分が最大フローのボトルネックになるので、S-Tカットと最大フローは等しくなる。
// 1,2より最大フローはS-Tカットと等しく、かつ最小カット以下なので、S-Tカット=最小カットになる

// 最小流量制約付き最大フロー問題: https://ikatakos.com/pot/programming_algorithm/graph_theory/maximum_flow

// Dinic法
// levelグラフを使うことでtから遠ざかるような無駄な経路を探索から除外して高速化を図っている
// またある頂点を再訪した時、一度使ったedgeは調べる必要がない(フローを増やせない。理由はdfsでそのedge以降のtまでの経路は全て探索済み)ので探索から除外できる
// 計算量: O(EV^2), ファルカーソンはO(FE)なので、基本はファルカーソンで考えて、流量が多い時はDinic法を検討する感じ

struct Edge {
    int to, cap, rev;
    Edge() {};
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8;
vector<vector<Edge>> G;
vector<int> level, iter;  // iter: どこまでチェックしたか

// sからの各頂点のlevelを計算
void bfs(int s) {
    queue<int> que; que.push(s);
    level[s] = 0;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto adj : G[v]) {
            // 残余ネットワークを考えるのでcap>0のedgeのみを見る
            if (level[adj.to] == -1 && adj.cap > 0) {
                level[adj.to] = level[v] + 1;
                que.push(adj.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;

    // 逆辺も含めて探索する
    for (int &i = iter[v]; i < G[v].size(); i++) {
        Edge &adj = G[v][i];
        // tに近づく方向にしか進まない(それ以外のedgeはtに到達するという目的では無駄な動きをすることになる)
        if (adj.cap > 0 && level[adj.to] > level[v]) {
            int d = dfs(adj.to, t, min(f, adj.cap));
            if (d > 0) {
                // 残余グラフを計算
                adj.cap -= d;
                G[adj.to][adj.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int main() {
    int n, m; cin >> n >> m;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < m; i++) {
        int from, to, cap; cin >> from >> to >> cap;
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, 0, G[from].size() - 1);
    }
    int s, t; cin >> s >> t;

    iter = vector<int>(n);
    level = vector<int>(n, -1);
    int ans = 0;
    // 高々V回: 最短経路長は最長でもV-1なのでO(V)になる
    while (1) {
        fill(level.begin(), level.end(), -1);
        bfs(s);  // O(E)
        // もうtに到達する経路が存在しないことを表す
        if (level[t] < 0) break;
        fill(iter.begin(), iter.end(), 0);
        while (1) {  // O(EV)
            int f = dfs(s, t, INF);
            if (f > 0) ans += f;
            else break;
        }
    }
    cout << ans << endl;
}
