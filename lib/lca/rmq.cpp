#include <bits/stdc++.h>
using namespace std;

// 根付き木を扱う問題はグラフを根からDFSし、その順に番号を付けて一列に並べて扱うとうまくいくことがよくある
// => 木を区間として扱えるので、seg木と相性が良い
//   例) 部分木をその最上位ノードvとして[v[in],v[out]]の区間として表現できる
//   例) LCAはその逆で、u,vの訪問番号に挟まれる位置に部分木の根があることを利用している

// ========================================
const int INF = 1e6;
int sz;
vector<int> dat;

// n: 要素数, a: 初期化時に利用する値
void rmq_init(int n, vector<int> a) {
    while (sz < n) sz *= 2;
    dat = vector<int>(sz * 2 - 1);
    a.resize(sz, 0);

    for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
    for (int i = sz - 2; i >= 0; i--) {
        dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
}

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
// ========================================

int root = 0;
vector<vector<int>> G;
vector<int> depth, vs, id;  // vs: dfsでの訪問順, id: 各頂点がvsに初めて登場するindex

void dfs(int v, int p, int d, int& k) {
    id[v] = k;  // 行きがけ順(pre-order)
    vs[k] = v;  // 行きも帰りも記録する
    depth[k++] = d;
    for (auto u : G[v]) {
        if (u != p) {
            dfs(u, v, d + 1, k);
            vs[k] = v;
            depth[k++] = d;
        }
    }
}

// 初期化
void init(int V) {
    // vs,depth,idを初期化する
    int k = 0;
    dfs(root, -1, 0, k);
    // RMQを初期化する(最小値ではなく、最小値のindexを返すようにする)
    rmq_init(V, depth);
}

// uとvのLCAを求める
int lca(int u, int v) {
    // queryによりdepthが最小になる訪問番号が分かるので、それをvsで引くことでノード番号を取得する
    return vs[query(min(id[u], id[v]), max(id[u], id[v]) + 1, 0, 0, sz).second];
}
