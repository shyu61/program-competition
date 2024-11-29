#include <bits/stdc++.h>
using namespace std;

// 根付き木を扱う問題はグラフを根からDFSし、その順に番号を付けて一列に並べて扱うとうまくいくことがよくある
// => 木を区間として扱えるので、seg木と相性が良い
//   例) 部分木をその最上位ノードvとして[v[in],v[out]]の区間として表現できる
//   例) LCAはその逆で、u,vの訪問番号に挟まれる位置に部分木の根があることを利用している

const int INF = numeric_limits<int>::max();
struct RMQ {
    vector<int> dat;
    int sz = 1;

    RMQ() {}
    // n: 要素数, a: 初期化時に利用する値
    RMQ(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<int>(sz * 2 - 1);

        for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // (value,index)
    // [a, b)の最小値を探索
    // k: ノード番号, [l, r)はそれに紐づく区間
    pair<int, int> query(int a, int b, int k, int l, int r) {
        // [a, b)と[l, r)が交差しない場合は解なし
        if (b <= l || r <= a) return make_pair(INF, -1);
        // [a, b)が[l, r)を完全に含んでいる時、このノードの値が解
        if (a <= l && r <= b) return make_pair(dat[k], k);
        else {
            auto [vl, il] = query(a, b, k * 2 + 1, l, (l + r) / 2);
            auto [vr, ir] = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl < vr ? make_pair(vl, il) : make_pair(vr, ir);
        }
    }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
};

vector<vector<int>> G;
vector<int> depth, preorder, id;  // preorder: dfsでの訪問順, id: 各頂点がpreorderに初めて登場するindex
RMQ rmq;

void dfs(int v, int p, int d, int& k) {
    id[v] = k;  // 行きがけ順(pre-order)
    preorder[k] = v;  // 行きも帰りも記録する
    depth[k++] = d;
    for (auto u : G[v]) {
        if (u != p) {
            dfs(u, v, d + 1, k);
            preorder[k] = v;
            depth[k++] = d;
        }
    }
}

// uとvのLCAを求める
int lca(int u, int v) {
    int s = min(id[u], id[v]);
    int t = max(id[u], id[v]);
    // queryによりdepthが最小になる訪問番号が分かるので、それをvsで引くことでノード番号を取得する
    return preorder[rmq.query(s, t + 1, 0, 0, rmq.sz).second];
}

int main() {
    int V; cin >> V;  // 木のノード数(要素数)

    // 初期化
    int k = 0;
    dfs(0, -1, 0, k);
    RMQ rmq(V, depth);

    // LCAを調べたい2頂点
    int u, v; cin >> u >> v;
    lca(u, v);
}
