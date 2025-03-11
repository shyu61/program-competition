#include <bits/stdc++.h>
#include <lib/union_find.cpp>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// | --          | Undirected | Directed | Functional |
// | Detect      | union-find | dfs      | union-find |
// | Reconstruct | dfs        | dfs      | union-find |

void undirect_cycle_detect() {
    int n, m;
    vector<P> es(m);  // edgeでループを回すのがシンプル

    UnionFind uf(n);
    bool has = false;
    for (auto [u, v] : es) {
        if (uf.same(u, v)) {
            has = true;
            break;
        }
        uf.merge(u, v);
    }
}

void directed_cycle_detection() {
    int n, m;
    vector<vector<int>> g(n);

    vector<int> seen(n);
    auto dfs = [&](auto dfs, int v) -> bool {
        seen[v] = 1;
        for (auto u : g[v]) {
            if (seen[u] == 2) continue;
            if (seen[u] == 1) return true;
            if (dfs(dfs, u)) return true;
        }
        seen[v] = 2;
        return false;
    };
    bool exist = dfs(dfs, 0);
}

void undirected_cycle_reconstruct() {
    int n, m;
    vector<vector<int>> g(n);

    vector<int> seen(n);
    vector<int> pre(n), cyc;
    auto dfs = [&](auto dfs, int v) -> bool {
        seen[v] = 1;
        for (auto u : g[v]) {
            if (seen[u] == 2) continue;
            if (seen[u] == 1) {
                // 通常の無向グラフのdfsではseenで逆流が抑制されるが、
                // seenを行きがけと帰りがけで区別しているので明示的に書く必要がある
                if (u == pre[v]) continue;
                cyc.push_back(v);
                int cur = v;
                while (cur != u) {
                    cyc.push_back(pre[cur]);
                    cur = pre[cur];
                }
                return true;
            } else {
                pre[u] = v;
                if (dfs(dfs, u)) return true;
            }
        }
        seen[v] = 2;
        return false;
    };
}

void directed_cycle_reconstruct() {
    int n, m;
    vector<vector<int>> g(n);

    vector<int> seen(n);
    vector<int> pre(n), cyc;
    auto dfs = [&](auto dfs, int v) -> bool {
        seen[v] = 1;
        for (auto u : g[v]) {
            if (seen[u] == 2) continue;
            if (seen[u] == 1) {
                cyc.push_back(v);
                int cur = v;
                while (cur != u) {
                    cyc.push_back(pre[cur]);
                    cur = pre[cur];
                }
                return true;
            } else {
                pre[u] = v;
                if (dfs(dfs, u)) return true;
            }
        }
        seen[v] = 2;
        return false;
    };
    dfs(dfs, 0);
    reverse(cyc.begin(), cyc.end());
}
