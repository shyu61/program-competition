#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<vector<int>> g;

    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v) {
        seen[v] = true;
        for (auto u : g[v]) {
            if (!seen[u]) dfs(dfs, u);
        }
    };

    auto dfs_st = [&](int v) {
        vector<bool> seen(n);
        stack<int> st;
        st.push(v);

        while (!st.empty()) {
            int v = st.top(); st.pop();
            if (seen[v]) continue;
            seen[v] = true;

            for (auto u : g[v]) {
                if (!seen[v]) st.push(u);
            }
        }
    };

    auto bfs = [&](int v) {
        queue<int> que;
        que.push(v);
        vector<int> dist(n, -1);
        dist[v] = 0;

        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto u : g[v]) {
                if (dist[u] != -1) continue;
                que.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    };
}

namespace tree {
    int N;
    vector<vector<int>> G(N);
    // seenでの再訪管理が不要

    void dfs(int v, int p) {
        for (auto adj : G[v]) {
            if (adj == p) continue;
            dfs(adj, v);
        }
    }
}

namespace grid {
    int H, W;
    vector<vector<int>> color(H, vector<int>(W));

    void dfs(int x, int y) {
        if (x == H) return;

        int nx = x + (y + 1) / W;
        int ny = (y + 1) % W;

        // 塗る場合
        color[nx][ny] = 1;
        dfs(nx, ny);
        color[nx][ny] = 0;

        // 塗らない場合
        dfs(nx, ny);
    }
}
