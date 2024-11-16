// No Cheating: p240
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// グリッド問題、組合せ最適化問題
// => 全探索、貪欲法、DP、グラフ
// 全探索: 2^nmは無理
// 貪欲法: 明らかに局所最適性は成立しない
// DP: ドミノ敷き詰めが類問として考えられそう。bitDPならO(nm*2^m)で無理
// グラフ: 頂点数の最大化,頂点の独立制約 => 最大安定集合

// 明らかにグラフと捉えて最大安定集合として解ける形に持っていくのが筋が良さそう
// -> 「最大安定集合 = V - 最小点カバー」で、二部グラフなら最大マッチングを求めれば良い
// -> なんとか二部グラフに帰着できるようにグラフを考えたい
// -> 座標系,グリッドの2部性といえば、x,yか偶奇か。よく見ると偶奇間でしかエッジがない
// -> 二部グラフに帰着できた

int M, N, V;
vector<vector<bool>> seats;
vector<vector<int>> G;
vector<int> match;
vector<bool> used;

vector<int> dx = {1,-1,1,-1}, dy = {0,0,-1,-1};

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

void addEdge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
}

int main() {
    cin >> M >> N;
    seats = vector<vector<bool>>(N, vector<bool>(M));
    int num = 0;
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            char c; cin >> c;
            if (c == 'x') seats[x][y] = true;
            else num++;
        }
    }

    V = M * N;
    G = vector<vector<int>>(V);
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            for (int r = 0; r < 4; r++) {
                if (seats[x][y]) continue;
                int nx = x + dx[r], ny = y + dy[r];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && !seats[nx][ny]) {
                    addEdge(y * N + x, ny * N + nx);
                }
            }
        }
    }

    cout << num - bipartiteMatching() << endl;
}
