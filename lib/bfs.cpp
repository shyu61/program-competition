#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> dist;
vector<vector<int>> G;

void bfs(int v) {
    queue<int> que;
    que.push(v);
    dist = vector<int>(n, -1);
    dist[v] = 0;

    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (auto adj : G[u]) {
            if (dist[adj] != -1) continue;
            que.push(adj);
            dist[adj] = dist[v] + 1;
        }
    }

}
