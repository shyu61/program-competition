// 応用問題(Asteroids): p205
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 二部グラフの最小点カバーに帰着させる問題
// 頂点をx,yそれぞれのビーム、辺を小惑星と見てグラフを作ると、全ての小惑星を破壊する最小のビームは、全ての辺をカバーする最小の頂点数と見ることができる

// 思考フロー
// グリッド問題 -> 全探索は無理そう、遷移も記述しにくそう -> グラフで考える -> 全ての小惑星をカバーする最小のビーム数なので、カバー問題に帰着できないか考える
// -> グリッドなので二部グラフと相性抜群であり、点はエッジとして表現するのが普通 -> 二部グラフの最小辺カバーに帰着 -> 最大マッチングとイコール

// 抽象化
// - グリッド問題はグラフと相性が良いが、x,yという明確な2つの区別がある性質上、二部グラフと相性が良い。
//   そして座標上の点はx,yをペアで持つので、二部グラフ上では頂点よりも辺としての方が圧倒的に表現しやすい（ここが直感とは逆なので注意）

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

const int INF = 2;
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

int bipartiteMatching(int N, int K, int s, int t) {
    return maxFlow(N + K, s, t);
}

int main() {
    int n, k; cin >> n >> k;

    G = vector<vector<Edge>>(n + n + 2);
    int s = n + n, t = s + 1;
    for (int i = 0; i < n; i++) addEdge(s, i, 1);
    for (int i = 0; i < n; i++) addEdge(i + n, t, 1);
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        addEdge(x, y + n, 1);
    }
    cout << bipartiteMatching(n, n, s, t) << endl;
}
