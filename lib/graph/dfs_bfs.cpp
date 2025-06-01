#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// 上下左右
const vector<int> dx = {1,-1,0,0,}, dy = {0,0,1,-1};

// grid
int main() {
    int h, w;
    vector<string> mas(h);
    auto bfs = [&](const vector<P>& vs) {
        queue<P> que;
        vector<vector<int>> dist(h, vector<int>(w, -1));
        // 多始点bfsにも対応
        for (auto [i, j] : vs) {
            que.emplace(i, j);
            dist[i][j] = 0;
        }

        while (!que.empty()) {
            auto [i, j] = que.front(); que.pop();
            rep(r, 4) {
                int ni = i + dx[r], nj = j + dy[r];
                if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                if (mas[ni][nj] != '.' || dist[ni][nj] != -1) continue;
                que.emplace(ni, nj);
                dist[ni][nj] = dist[i][j] + 1;
            }
        }
    };

    vector<vector<bool>> seen(h, vector<bool>(w));
    auto dfs = [&](auto dfs, int v) -> int {
        rep(r, 4) {
            int ni = i + dx[r], nj = j + dy[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != '.' || seen[ni][nj]) continue;
            seen[ni][nj] = true;
            dfs(dfs, ni, nj);
        }
    };
}

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

    vector<vector<P>> G;
    auto bfs01 = [&](int v) {
        deque<int> deq;
        deq.push_front(v);
        vector<int> dist(n, INF);
        dist[v] = 0;

        while (!deq.empty()) {
            int v = deq.front(); deq.pop_front();
            for (auto [u, w] : G[v]) {
                if (dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;
                    if (w == 0) deq.push_front(v);
                    else deq.push_back(v);
                }
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

    auto dfs = [&](auto dfs, int v, int p = -1) -> void {
        for (auto u : g[v]) {
            if (u == p) continue;
            dfs(dfs, u, v);
        }
    };
    dfs(dfs, 0);

    int n;
    vector<int> dist(n);
    auto dfs_dist = [&](auto dfs_dist, int v, int p = -1, int dep = 0) -> P {
        dist[v] = dep;
        P res(dep, v);
        for (auto u : g[v]) {
            if (u == p) continue;
            res = max(res, dfs_dist(dfs_dist, u, v, dep + 1));
        }
        return res;
    };
    auto [_, a] = dfs_dist(dfs_dist, 0);
    auto [diameter, b] = dfs_dist(dfs_dist, a);
}
