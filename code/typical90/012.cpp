#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 到達可能性問題, 連結成分問題, グリッド問題, クエリ問題

// 方針
// まずクエリ問題として考えてみる。 最もnaiveな方法は各クエリでdfsする方法だが、TLEする
// また動的クエリかつ、オンラインで処理する必要があるので、部分事前計算の可能性が高い
// 部分事前計算は何からのデータ構造を使うことがほとんどという前提を置く
// 次に、到達可能性問題としての側面を考える。連結成分問題とくればunionfindによる高速化を考える
// 十分に高速に処理できることがわかる

// ポイント
// 到達可能性問題とくればunionfind

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }
};

const vector<int> dx = {0,1,0,-1};
const vector<int> dy = {1,0,-1,0};

int main() {
    int h, w, q; cin >> h >> w >> q;
    vector<vector<bool>> mas(h, vector<bool>(w));

    UnionFind uf(h * w);

    rep(i, q) {
        int type; cin >> type;
        if (type == 1) {
            int r, c; cin >> r >> c; r--, c--;
            mas[r][c] = true;
            rep(i, 4) {
                int nx = r + dx[i], ny = c + dy[i];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
                if (mas[nx][ny]) uf.merge(r * w + c, nx * w + ny);
            }
        } else {
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            r1--, c1--, r2--, c2--;
            bool ok = true;
            if (!mas[r1][c1] || !mas[r2][c2]) ok = false;
            if (!uf.same(r1 * w + c1, r2 * w + c2)) ok = false;
            cout << (ok ? "Yes" : "No") << '\n';
        }
    }
}
