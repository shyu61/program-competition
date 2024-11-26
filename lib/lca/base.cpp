#include <bits/stdc++.h>
using namespace std;

// 初期化: O(nlogn), クエリ: O(logn)

const int MAX_LOG_V = 1e4;  // FIXME
int root;
vector<vector<int>> G, parent;  // parent[k][v]: vから親を2^k回辿って到達する頂点(根を通り過ぎる場合は-1)
vector<int> depth;

void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (auto u : G[v]) {
        if (u != p) dfs(u, v, d + 1);
    }
}

// 初期化
void init(int V) {
    // parent[0]とdepthを初期化する
    dfs(root, -1, 0);
    // parentを初期化する
    for (int k = 0; k + 1 < MAX_LOG_V; k++) {
        for (int v = 0; v < V; v++) {
            if (parent[k][v] < 0) parent[k + 1][v] = -1;  // 2^k回で既に根を通り過ぎている場合
            else parent[k + 1][v] = parent[k][parent[k][v]];
        }
    }
}

// uとvのLCAを求める
int lca(int u, int v) {
    // uとvの深さを揃える
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < MAX_LOG_V; k++) {
        // この操作ができるのは、2の累乗和(2進数)で全ての整数を表現できるからである
        // 必ずピッタリdepth[v]-depth[u]だけ上ることができる
        if ((depth[v] - depth[u] >> k & 1)) {
            v = parent[k][v];
        }
        if (u == v) return u;
    }
    // 二分探索でLCAを求める(同じ頂点に到達するまで親を辿る)
    // 二分探索を考える時は、lbは常に条件を満たさない、ubは常に条件を満たすようにとる
    // u,vはlbに該当し、条件を満たさない(parentが一致しない)場合はそこまでlbを動かせるので更新する
    for (int k = MAX_LOG_V - 1; k >= 0; k--) {
        if (parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    // u,vは条件を満たさない最大値になるので、その親が答えになる
    return parent[0][u];
}
