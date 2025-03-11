#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// lowlink法: O(V+E)
int main() {
    int n, m;
    vector<vector<int>> g(n);

    vector<int> ord(n), low(n);
    vector<P> bg;
    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v, int p, int i) -> void {
        seen[v] = true;
        ord[v] = low[v] = i;
        for (auto u : g[v]) {
            if (!seen[u]) {
                dfs(dfs, u, v, i + 1);
                // 子で自身より小さいlowを持つ(backedgeを持つ)ものがあれば、
                // 自分もその子経由でそこへ移動できることになる
                low[v] = min(low[v], low[u]);
                // 自分より上の(訪問番号が小さい)ノードへ行ける子が存在しない時、橋になる
                if (ord[v] < low[u]) bg.emplace_back(v, u);
            } else if (u != p) {
                // 後退辺の場合
                // 無向グラフなので、seen[u]が単なる親への逆流の場合を除外する必要がある
                low[v] = min(low[v], ord[u]);
            }
        }
    };

    dfs(dfs, 0, -1, 0);
}
