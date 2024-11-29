#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

// 根付き木を扱う問題はグラフを根からDFSし、その順に番号を付けて一列に並べて扱うとうまくいくことがよくある
// => 木を区間として扱えるので、seg木と相性が良い
//   例) 部分木をその最上位ノードvとして[v[in],v[out]]の区間として表現できる
//   例) LCAはその逆で、u,vの訪問番号に挟まれる位置に部分木の根があることを利用している

const int INF = numeric_limits<int>::max();
struct RMQ {
    vector<P> dat;
    int sz = 1;

    RMQ() {}
    // n: 要素数, a: 初期化時に利用する値
    RMQ(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<P>(sz * 2 - 1, make_pair(INF, -1));

        for (int i = 0; i < n; i++) dat[i + sz - 1] = make_pair(a[i], i);
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // (value,index)
    P query(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return make_pair(INF, -1);
        if (a <= l && r <= b) return dat[k];
        else {
            P vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            P vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k].first = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
};

vector<vector<int>> G;
// tour: dfsでの訪問順, preorder: 各頂点がtourに初めて登場するindex
vector<int> depth, tour, preorder;
RMQ rmq;

void dfs(int v, int p, int d, int& k) {
    preorder[v] = k;  // 行きがけだけ記録
    tour[k] = v;
    depth[k++] = d;
    for (auto u : G[v]) {
        if (u != p) {
            dfs(u, v, d + 1, k);
            tour[k] = v;
            depth[k++] = d;
        }
    }
}

int lca(int u, int v) {
    // セグ木やBITは重複を含む訪問番号で作られているので、queryするときは訪問番号を使う
    // lcaの戻り値はノード番号なので、tourで訪問番号からノード番号に変換する
    int s = min(preorder[u], preorder[v]);
    int t = max(preorder[u], preorder[v]);
    return tour[rmq.query(s, t + 1, 0, 0, rmq.sz).second];
}

int main() {
    int n; cin >> n;
    G = vector<vector<int>>(n);

    // 初期化
    depth = tour = vector<int>(n * 2 - 1);
    preorder = vector<int>(n);
    int k = 0;
    dfs(0, -1, 0, k);
    rmq = RMQ(n * 2 - 1, depth);

    int u, v; cin >> u >> v;
    lca(u, v);
}
