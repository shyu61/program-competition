#include <bits/stdc++.h>
using namespace std;

// LCA: 最小共通祖先

int root;
vector<vector<int>> G;
vector<int> parent, depth;  // 根ノードの親は-1とする

void dfs(int v, int p, int d) {
    parent[v] = p;
    depth[v] = d;
    for (auto u : G[v]) {
        if (u != p) dfs(u, v, d + 1);
    }
}

// 初期化
void init() {
    // parentとdepthを初期化する
    dfs(root, -1, 0);
}

// uとvのLCAを求める
int lca(int u, int v) {
    // uとvの深さを揃える
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];

    // 同じ頂点に到達するまで親を辿る
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}
