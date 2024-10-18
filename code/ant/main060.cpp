// 応用問題(Conscription): p103
#include <bits/stdc++.h>
using namespace std;

// prim法とkruskal法は計算量もほぼ同じで、どちらも負の重みを扱えるので違いはほとんどない。
// しかしkruskalはグラフが連結でない場合はmstの森の合計を求めることができるという性質を持っている。
// これはprim法が徐々にmstを成長させていくのに対して、kruskalはmstのパーツそれぞれで成長し最終的に1つにmergeするという成長戦略をとっていることに起因する。

struct UnionFind {
    // 親のインデックスを保持する
    // rootは負の値を取り、その絶対値がその木における要素数を表す
    vector<int> par;

    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }

    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);  // 経路圧縮
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        // 常に小さい木を大きい木に結合する
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }
};

struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {};
    bool operator<(const Edge &other) const {
        return cost < other.cost;
    };
};

const int C = 10000;
int r, V;
vector<Edge> E;

int kruskal() {
    sort(E.begin(), E.end());
    UnionFind uf(V);
    int total = 0;
    for (auto e : E) {
        if (uf.same(e.from, e.to)) continue;
        uf.unite(e.from, e.to);
        total += e.cost;
    }

    return total;
}

int main() {
    int n, m; cin >> n >> m >> r;
    V = n + m;
    for (int i = 0; i < r; i++) {
        int x, y, cost; cin >> x >> y >> cost;
        E.emplace_back(x, y + n, -cost);
    }
    cout << C * V + kruskal() << endl;
}

// ================================================
// prim法による別解

struct Edge {
    int to, cost;
    Edge(int to, int cost) : to(to), cost(cost) {};
};

const int C = 10000;
int n, m, V;
vector<vector<Edge>> G;
vector<bool> used;

int prim(int s) {
    vector<bool> in_mst(V);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    used[s] = true;

    int total = 0;
    while (!pq.empty()) {
        auto [cost, v] = pq.top(); pq.pop();

        if (in_mst[v]) continue;

        total += cost;
        used[v] = true;
        in_mst[v] = true;

        for (auto adj : G[v]) {
            if (!in_mst[adj.to]) {
                pq.emplace(adj.cost, adj.to);
            }
        }
    }
    return total;
}

int main() {
    int r; cin >> n >> m >> r;
    V = n + m;
    G = vector<vector<Edge>>(V);
    used = vector<bool>(V);
    for (int i = 0; i < r; i++) {
        int x, y, cost; cin >> x >> y >> cost;
        y += n; cost = -cost;
        G[x].emplace_back(y, cost);
        G[y].emplace_back(x, cost);
    }
    int total = C * V;
    for (int i = 0; i < V; i++) {
        if (!used[i]) total += prim(i);
    }
    cout << total << endl;
}
