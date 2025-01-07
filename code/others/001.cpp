// 有向グラフの閉路検出: dfs
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> G;
vector<int> color;

bool dfs(int v) {
    color[v] = 1;
    for (auto adj : G[v]) {
        if (color[adj] == 2) continue;
        if (color[adj] == 1){
            return true;
        }
        if (dfs(adj)) return true;
    }
    color[v] = 2;
    return false;
}

int main() {
    int N, M; cin >> N >> M;
    G = vector<vector<int>>(N);
    color = vector<int>(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }

    for (int i = 0; i < N; i++) {
        if (color[i] == 2) continue;
        if (dfs(i)) {
            cout << 1 << endl;
            return 0;
        }
    }

    cout << 0 << endl;
}
