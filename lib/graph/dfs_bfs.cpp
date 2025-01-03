#include <bits/stdc++.h>
using namespace std;

namespace graph {
    int N;
    vector<vector<int>> G(N);
    vector<bool> seen(N);

    void dfs(int v) {
        seen[v] = true;
        for (auto adj : G[v]) {
            if (seen[adj]) continue;
            dfs(adj);
        }
    }

    void dfs_stack(int v) {
        stack<int> st;
        st.push(v); seen[v] = true;

        while (!st.empty()) {
            int v = st.top();
            int nxt = -1;
            for (auto adj : G[v]) {
                if (seen[adj]) continue;
                st.push(adj); seen[adj] = true;
                nxt = adj;
                break;
            }
            if (nxt == -1) st.pop();
        }
    }

    const int INF = 1e8; // FIXME
    vector<int> dist(N, INF);

    void bfs(int v) {
        queue<int> que;
        que.push(v); seen[v] = true; dist[v] = 0;

        while (!que.empty()) {
            int u = que.front(); que.pop();

            for (auto adj : G[u]) {
                if (seen[adj]) continue;
                que.push(adj); seen[adj] = true; dist[adj] = dist[u] + 1;
            }
        }
    }
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
