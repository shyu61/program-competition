#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 初期化: O(nlogn), クエリ: O(logn)
int main() {
    int n;
    vector<vector<int>> g(n);

    // 前処理
    const int LOG = 17;
    vector<int> depth(n);
    vector<vector<int>> parent(LOG, vector<int>(n));  // parent[i][j]:=jから親を2^i辿った先の頂点
    auto dfs = [&](auto dfs, int v, int p, int d) -> void {
        parent[0][v] = p;
        depth[v] = d;
        for (auto to : g[v]) {
            if (to == p) continue;
            dfs(dfs, to, v, d + 1);
        }
    };
    dfs(dfs, 0, -1, 0);
    rep(i, LOG - 1) {
        rep(j, n) {
            if (parent[i][j] < 0) parent[i + 1][j] = -1;
            else parent[i + 1][j] = parent[i][parent[i][j]];
        }
    }

    auto lca = [&](int u, int v) -> int {
        if (depth[u] > depth[v]) swap(u,v);
        rep(i, LOG) {
            // depth[v]-depth[u] だけ上るには、これを2進数で表した時に1が立っている桁の時にparentを辿れば良い
            if (depth[v] - depth[u] >> i & 1) {
                v = parent[i][v];
            }
        }
        if (u == v) return u;

        // 二分探索
        // parentが一致する限りdoublingで減らして行き、一致しない時は親に登って再度doublingで減らす
        for (int i = LOG - 1; i >= 0; i--) {
            // lca以上は必ず一致するので、一致しない時点でlbを更新する
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        // u,vは条件を満たさない最大値になるので、その親が答えになる
        return parent[0][u];
    };
}
