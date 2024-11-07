#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int V;
vector<vector<int>> G;
vector<int> match;
vector<bool> used;

// 増加パスの探索
bool dfs(int v) {
    used[v] = true;

    for (auto u : G[v]) {
        int w = match[u];
        // 未マッチが見つかれば終了
        // マッチ済みならさらに探索(マッチ先からの遷移先ノードとは絶対ペアにならないので、結果交互に未マッチ/マッチが現れることになる)
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int bipartiteMatching() {
    // maxFlow(s, t)でもOK。その場合s,tを別途用意してV += 2する必要がある
    match = vector<int>(V, -1);
    used = vector<bool>(V);
    int res = 0;
    // Nでも良いが、片方の頂点群を始点とする場合のみ調べれば十分
    for (int i = 0; i < V; i++) {
        if (match[i] >= 0) continue;
        fill(used.begin(), used.end(), false);
        if (dfs(i)) res++;
    }
    return res;
}

int main() {
    int N, K, M; cin >> N >> K >> M;
    V = N + K;
    G = vector<vector<int>>(V);
    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        x--; y = y + N - 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cout << bipartiteMatching() << endl;
}
