#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

using Graph = vector<vector<int>>;

Graph G;

vector<bool> seen;
void dfs(int v) {
    seen[v] = true;

    for (auto adj : G[v]) {
        if (seen[adj]) continue;
        dfs(adj);
    }
}

// 探索対象が木の場合
void dfs_tree(int v, int p) {
    for (auto adj : G[v]) {
        // 親には戻らない
        if (adj == p) continue;
        dfs_tree(adj, v);
    }
}

void dfs_stack(int v) {
    stack<int> st;
    st.push(v); seen[v] = true;

    while (!st.empty()) {
        int v = st.top();

        int forward = -1;
        for (auto adj : G[v]) {
            if (!seen[adj]) {
                st.push(adj);
                seen[adj] = true;
                forward = adj;
                break;
            }
        }
        if (forward == -1) st.pop();
    }
}

const int NMAX = 1e5;
int dist[NMAX];
void bfs(int v) {
    queue<int> que;
    que.push(v); seen[v] = true;

    dist[v] = 0;
    while (!que.empty()) {
        int v = que.front(); que.pop();

        for (auto adj : G[v]) {
            if (seen[adj]) continue;
            que.push(adj);
            seen[adj] = true;
            dist[adj] = dist[v] + 1;
        }
    }
}


// グリッド問題の全探索
// 左上から順に決定していく
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
