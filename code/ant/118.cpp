// Wi-fi Towers: p250
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 組合せ最適化問題で、最終的に2つの部分集合を構築したい時は最小カットを検討する
// 最小カットはOR条件であり、重複なくどちらかの部分集合に割り当てたい一種の割当問題とも言える
// 「必ず同じ方に割当てないといけない」や「別のグループに割当てた場合のペナルティ」といった制約はうまく表現できる

// 最小カットについて: https://ikatakos.com/pot/programming_algorithm/graph_theory/maximum_flow/burn_bury_problem

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 501;  // 重みの最大値
int V;
vector<vector<Edge>> G;
vector<bool> used;

void add_edge(int from, int to, int cap) {
    G[from].emplace_back(to, cap, G[to].size());
    G[to].emplace_back(from, 0, G[from].size() - 1);
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;

    // 逆辺も含めて探索する
    for (auto &adj : G[v]) {
        if (!used[adj.to] && adj.cap > 0) {
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

int max_flow(int s, int t) {
    used = vector<bool>(V);

    int res = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) res += f;
        else break;
    }
    return res;
}

int main() {
    int N; cin >> N;
    vector<int> x(N), y(N), r(N), S(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i] >> r[i] >> S[i];

    // sink: プロトコルB, source: プロトコルA への割当と考える
    int s = N, t = s + 1;
    V = N + 2;
    G = vector<vector<Edge>>(V);
    int res = 0;
    for (int i = 0; i < N; i++) {
        // sinkに割当てるコストは-S[i]
        if (S[i] < 0) add_edge(i, t, -S[i]);
        else {
            res += S[i];
            // sinkに割当てるコストは-S[i]だが、最小カットで解く場合負のcapは扱えないので、
            // sourceに割当てるコストがS[i]と考える
            add_edge(s, i, S[i]);
        }

        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            double d2 = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            // 異なる方へは割当てられないのでINFのエッジを張る
            if (r[i] * r[i] >= d2) add_edge(i, j, INF);
        }
    }

    cout << res - max_flow(s, t) << endl;
}
