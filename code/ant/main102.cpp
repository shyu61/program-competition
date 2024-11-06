// 応用問題(Dining): p210
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 明らかに割当問題なので二部マッチングで解けないか考える -> カテゴリーが3種類なので工夫してなんとか2部マッチングに帰着できないか考える
// -> ペア関係にあるのは「牛-食べ物」「牛-飲み物」の2つなので、それぞれで2部グラフを作ってうまく繋ぎ合わせることを考える
// -> 牛は両方の2部グラフで1度しか使えないという制約があるので、これはノード制約と見ることができる
// -> ノード制約とくれば、ノードを複製してその間のエッジの容量で制約を表現するのが定石
// -> あとは最大フローのアプローチで二部マッチングを解けば良い

// 二部マッチングのアルゴリズムの使い分け
// 最大フロー: 制約条件などが複雑なケース、グラフが静的な場合
// 増加パス: 順番待ちなどグラフが動的なケース、複雑な制約は表現が難しい

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 101;  // 牛の数 + 1
vector<vector<Edge>> G;
vector<bool> used;

void addEdge(int from, int to, int cap) {
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

int maxFlow(int n, int s, int t) {
    used = vector<bool>(n);

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
    int N, F, D; cin >> N >> F >> D;
    vector<vector<int>> fd(N), dr(N);
    cin.ignore();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            string l;
            getline(cin, l);
            istringstream stream(l);
            int num;
            if (j == 0) while (stream >> num) fd[i].push_back(--num);
            else while (stream >> num) dr[i].push_back(--num);
        }
    }

    int V = N * 2 + F + D + 2;
    int s = N * 2 + F + D, t = s + 1;
    G = vector<vector<Edge>>(V);

    for (int i = 0; i < F; i++) addEdge(s, i, 1);
    for (int i = 0; i < N; i++) addEdge(F + i, F + N + i, 1);
    for (int i = 0; i < D; i++) addEdge(F + N * 2 + i, t, 1);
    for (int i = 0; i < N; i++) {
        for (auto v : fd[i]) addEdge(v, F + i, 1);
        for (auto v : dr[i]) addEdge(F + N + i, F + N * 2 + v, 1);
    }
    
    cout << maxFlow(V, s, t) << endl;
}
