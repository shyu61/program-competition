#include <bits/stdc++.h>
using namespace std;

void graph() {
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

void tree() {
    vector<vector<int>> g;

    auto dfs = [&](auto dfs, int v, int p) -> void {
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v);
        }
    };
    dfs(dfs, 0, -1);
}

void grid() {
    const vector<int> dx = {1,0,0,1}, dy = {0,1,-1,0};

    int h, w;
    vector<string> mas(h);

    auto dfs = [&](auto dfs, int i, int j) -> void {
        rep(r, 4) {
            int nh = i + dx[r], nw = j + dy[r];
            if (nh < 0 || nh >= h || nw < 0 || nw >= h) continue;
            if (mas[nh][nw] != '.') continue;
            mas[nh][nw] = 'x';
            dfs(dfs, nh, nw);
        }
    };
}
