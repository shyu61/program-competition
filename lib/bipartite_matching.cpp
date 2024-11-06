#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

int bipartiteMatching(int N) {
    match = vector<int>(N, -1);
    used = vector<bool>(N);
    int res = 0;
    // Nでも良いが、片方の頂点群を始点とする場合のみ調べれば十分
    for (int i = 0; i < N; i++) {
        if (match[i] >= 0) continue;
        fill(used.begin(), used.end(), false);
        if (dfs(i)) res++;
    }
    return res;
}

int main() {
    int N, K, M; cin >> N >> K >> M;
    G = vector<vector<int>>(N + K);
    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        x--; y = y + N - 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    cout << bipartiteMatching(N + K) << endl;
}
