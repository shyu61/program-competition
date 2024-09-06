// E - Sinking Land
// https://atcoder.jp/contests/abc363/tasks/abc363_e
// union-findを使った場合
#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    // 親のインデックスを保持する
    // rootは負の値を取り、その絶対値がその木における要素数を表す
    vector<int> par;

    UnionFind() {}
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

struct Section {
    int e, id;
    Section () {}
    Section (int e): e(e) {}
    Section (int e, int id): e(e), id(id) {}
    bool operator<(const Section& other) const { return e < other.e; };
};

const int H_MAX = 1000;
const int W_MAX = 1000;
const int Y_MAX = 1e5;
int h, w, y, e[H_MAX][W_MAX];
vector<Section> es;
UnionFind uf;

int horizon[4] = {1, 0, -1, 0};
int vertical[4] = {0, 1, 0, -1};

int solve(int year, int start) {
    int end = upper_bound(es.begin(), es.end(), Section(year)) - es.begin();

    for (int id = start; id < end; id++) {
        int i = es[id].id;
        int dh = i / w;
        int dw = i % w;
        if (e[dh][dw] <= year) {
            for (int r = 0; r < 4; r++) {
                int adjh = dh + horizon[r];
                int adjw = dw + vertical[r];
                int adj = adjh * w + adjw;
                if (adjh >= 0 && adjh < h && adjw >= 0 && adjw < w) {
                    if (e[adjh][adjw] <= year) uf.unite(i, adj);
                } else {
                    // 外周は海(h*w)のunion-treeと隣接していると考える
                    uf.unite(i, h * w);
                }
            }
        }
    }

    cout << h * w - (uf.size(h * w) - 1) << endl;

    return end;
}

int main() {
    cin >> h >> w >> y;
    es.reserve(H_MAX * W_MAX);
    uf = UnionFind(h * w + 1);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> e[i][j];
            es.push_back(Section(e[i][j], i * w + j));
        }
    }

    sort(es.begin(), es.end());

    int start = 0;
    for (int year = 1; year <= y; year++) {
        start = solve(year, start);
    }
}
