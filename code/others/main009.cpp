// LCA
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

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
vector<int> depth, tour, preorder;
RMQ rmq;

void dfs(int v, int p, int d, int& k) {
    preorder[v] = k;
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
    int s = min(preorder[u], preorder[v]);
    int t = max(preorder[u], preorder[v]);
    return tour[rmq.query(s, t + 1, 0, 0, rmq.sz).second];
}

int main() {
    int n; cin >> n;
    G = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int c; cin >> c;
            G[i].push_back(c);
            G[c].push_back(i);
        }
    }

    // 初期化
    depth = tour = vector<int>(n * 2 - 1);
    preorder = vector<int>(n);
    int k = 0;
    dfs(0, -1, 0, k);
    rmq = RMQ(n * 2 - 1, depth);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}
