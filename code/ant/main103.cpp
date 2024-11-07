// 応用問題(Dual Core CPU): p212
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 割当問題の多くはネットワークフロー関連のアルゴリズムで解けるが、いつもマッチングとは限らない
// 本問題のように「OR条件」かつ「コスト最小化」のケースでは最小カットで考える。
// 割当先が2つある場合は3種類になるので二部マッチングで解く場合は拡張する必要があるが、2つの二部グラフの結合は基本「AND条件」である。
// つまり、両方の二部グラフに共通で含まれるカテゴリーをキーにするケースである
// また、異なるペア間に制約がある場合は、マッチングでは表現しにくく、カットだとより直感的に表現できる

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 1e8; // w[i]の合計の最大値
int V;
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

int maxFlow(int s, int t) {
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
    int N, M; cin >> N >> M;
    vector<int> A(N), B(N), a(M), b(M), w(M);
    for (int i = 0; i < N; i++) cin >> A[i] >> B[i];
    for (int i = 0; i < M; i++) {
        cin >> a[i] >> b[i] >> w[i];
        --a[i]; --b[i];
    }

    V = N + 2;
    G = vector<vector<Edge>>(V);
    int s = N, t = s + 1;
    for (int i = 0; i < N; i++) {
        addEdge(s, i, B[i]);
        addEdge(i, t, A[i]);
    }
    for (int i = 0; i < M; i++) {
        addEdge(a[i], b[i], w[i]);
        addEdge(b[i], a[i], w[i]);
    }

    cout << maxFlow(s, t) << endl;
}
