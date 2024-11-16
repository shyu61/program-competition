// Stock Charts: p242
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// DAGの最小パス被覆問題: 二部グラフの最大マッチング問題に帰着できる
// マッチングはその2頂点が元のグラフで同じpathに含まれることを示す。逆にマッチングがない頂点はその頂点へ入るpathがない、つまりパスの始点か孤立点のどちらか
// マッチングの最大化はパスの始点数の最小化であり、パスの個数の最小化になる

// 思考フロー
// 組合せ最適化問題の一種。但し全体として1つの集合を考えるのではなく、複数の部分集合を考えてその個数を最小化するという、やや特殊な問題設定
// そもそも条件を記述するのが難しい。「交差の禁止」をどう表現するか -> 交差はペア間の関係性によって記述できる -> ペア間の条件を表現する方法と言えばグラフ
// -> グラフのエッジとして交差する あるいは 交差しないを表現させておくことを考える
// -> 最終的には互いに交差しない部分集合を作りたいので、エッジは「交差しないチャート間」に張るのが良さそう
// -> エッジで繋がった頂点同士を部分集合として、部分集合の個数を最小化したい -> 最小パスカバーに帰着

// 最小パスカバー: DAGの依存関係を満たす部分集合数の最小化

int V;
vector<vector<int>> G;
vector<int> match;
vector<bool> used;

// 増加パスの探索
bool dfs(int v) {
    used[v] = true;

    for (auto u : G[v]) {
        int w = match[u];
        // 未マッチが見つかれば終了
        // マッチ済みならさらに探索(マッチ先からの遷移先ノードとは絶対ペアにならないので、結果交互に未マッチ/マッチが現れることになる)
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int bipartiteMatching() {
    // maxFlow(s, t)でもOK。その場合s,tを別途用意してV += 2する必要がある
    match = vector<int>(V, -1);
    used = vector<bool>(V);
    int res = 0;
    // Nでも良いが、片方の頂点群を始点とする場合のみ調べれば十分
    for (int i = 0; i < V; i++) {
        if (match[i] >= 0) continue;
        fill(used.begin(), used.end(), false);
        if (dfs(i)) res++;
    }
    return res;
}

int main() {
    int N, K; cin >> N >> K;
    vector<vector<int>> S(N, vector<int>(K));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> S[i][j];
        }
    }

    V = 2 * N;
    G = vector<vector<int>>(V);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            bool above = true;
            for (int k = 0; k < K; k++) {
                if (S[i][k] <= S[j][k]) {
                    above = false;
                    break;
                }
            }
            // 自身より上に描けるチャートへエッジを張る
            if (above) {
                G[i].push_back(j + N);
                G[j + N].push_back(i);
            }
        }
    }

    cout << N - bipartiteMatching() << endl;
}
