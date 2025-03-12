#include <bits/stdc++.h>
using namespace std;

void graph() {
    int n;
    vector<vector<int>> g;

    vector<bool> seen(n);
    auto dfs = [&](auto dfs, int v) -> void {
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

    // 全パス列挙
    vector<int> path;
    auto dfsa = [&](auto dfsa, int v, int t) -> void {
        seen[v] = true;
        path.push_back(v);

        if (v == t) {
            for (auto v : path) cout << v << ' ';
            cout << endl;
        } else {
            for (auto u : g[v]) {
                if (!seen[u]) dfsa(dfsa, u, t);
            }
        }

        seen[v] = false;
        path.pop_back();
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
    const vector<int> dh = {1,0,0,1}, dw = {0,1,-1,0};

    int h, w;
    vector<string> mas(h);

    vector<vector<bool>> seen(h, vector<bool>(w));
    auto dfs = [&](auto dfs, int i, int j) -> void {
        rep(r, 4) {
            int ni = i + dh[r], nj = j + dw[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != '.' || seen[ni][nj]) continue;
            seen[ni][nj] = true;
            dfs(dfs, ni, nj);
        }
    };
}
