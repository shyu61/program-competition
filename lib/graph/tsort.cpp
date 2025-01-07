#include <bits/stdc++.h>
using namespace std;

namespace bfs_based_tsort {
    vector<vector<int>> G;
    vector<int> ts, in_deg;
    vector<bool> used;

    void bfs(int s) {
        queue<int> que;
        que.push(s); ts.push_back(s); used[s] = true;
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto adj : G[v]) {
                if (used[adj]) continue;
                in_deg[adj]--;
                if (in_deg[adj] == 0) {
                    que.push(adj); ts.push_back(adj); used[adj] = true;
                }
            }
        }
    }

    void tsort(int N) {
        for (int i = 0; i < N; i++) {
            if (used[i] || in_deg[i] != 0) continue;
            bfs(i);
        }
    }
}

namespace dfs_based_tsort {
    vector<vector<int>> G;
    vector<int> ts, in_deg;
    vector<bool> used;

    void dfs(int v) {
        used[v] = true;
        for (auto adj : G[v]) {
            if (used[adj]) continue;
            dfs(adj);
        }
        ts.push_back(v);
    }

    void tsort(int N) {
        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            dfs(i);
        }
    }
}
