// MST: クラスカル法
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

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
    int source, target, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    };
};

vector<Edge> E;
int n_node, n_edge;

int kruskal() {
    int total = 0;
    UnionFind uf(n_node);
    sort(E.begin(), E.end());

    // 木のエッジ数は必ず`n_node-1`になる
    for (int i = 0; i < n_edge; i++) {
        Edge e = E[i];
        if (!uf.same(e.source, e.target)) {
            uf.unite(e.source, e.target);
            total += e.w;
        }
    }
    return total;
}

int main() {
    cin >> n_node >> n_edge;
    E = vector<Edge>(n_edge);

    for (int i = 0; i < n_edge; i++) {
        int s, t, w; cin >> s >> t >> w;
        E[i] = (Edge{s, t, w});
    }

    cout << kruskal() << endl;
}
