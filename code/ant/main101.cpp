// 応用問題(Evacuation): p206
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 最寄りのドアを使いたい -> 距離によって到達時間が変わる -> 最寄りのドアからの距離が最大のものを求めれば良い? -> 毎秒1人しかドアを通過できない制約を考慮できない
// -> 各時刻でドアに到達可能な人のうち、通過する人を割当れば良い(割当問題、順番待ち問題) -> ドアと人で二部マッチングに帰着

// 抽象化
// いわゆる割当問題。異なる2つのカテゴリー間で二部グラフを作成する類の問題
// 人/タスク/物品/価値などの割当、スケジューリングなどがよくある。
// リソース(時間/コスト/容量)などに制限がある場合や、順番待ちなども割当問題に帰着することが多い。

const int INF = 12 * 12 * 2;  // 全ての点からの水が集中した場合+1
const vector<int> dx = {1,0,-1,0}, dy = {0,1,0,-1};
vector<pair<int, int>> doors, ppl;
int X, Y;
vector<vector<char>> R;
vector<int> match;
vector<bool> used;
vector<vector<int>> G;
vector<vector<vector<vector<int>>>> dist;

// ======================================================================
bool dfs(int v) {
    used[v] = true;

    for (auto u : G[v]) {
        int w = match[u];
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
    for (int i = 0; i < N; i++) {
        if (match[i] >= 0) continue;
        fill(used.begin(), used.end(), false);
        if (dfs(i)) res++;
    }
    return res;
}
// ======================================================================

vector<vector<int>> bfs(int x, int y) {
    queue<pair<int, int>> que;
    vector<vector<int>> d(X, vector<int>(Y, -1));
    que.emplace(x, y);
    d[x][y] = 0;

    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        for (int r = 0; r < 4; r++) {
            int nx = x + dx[r], ny = y + dy[r];
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && d[nx][ny] == -1 && R[nx][ny] == '.') {
                d[nx][ny] = d[x][y] + 1;
                que.emplace(nx, ny);

            }
        }
    }
    return d;
}

// 時刻tで全員脱出できるかどうか
bool check(int t) {
    int dsize = doors.size() * t, psize = ppl.size();
    int N = dsize + psize;
    G = vector<vector<int>>(N);

    for (int i = 0; i < doors.size(); i++) {
        for (int j = 0; j < psize; j++) {
            int d = dist[doors[i].first][doors[i].second][ppl[j].first][ppl[j].second];
            if (d == -1) continue;
            // 時刻dt以内にドアに到達可能な人に対してedgeを張る
            for (int dt = d; dt <= t; dt++) {
                G[(dt - 1) * doors.size() + i].push_back(dsize + j);
            }
        }
    }
    return bipartiteMatching(N) == psize;
}

int main() {
    cin >> X >> Y;
    R = vector<vector<char>>(X, vector<char>(Y));
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) cin >> R[x][y];
    }

    // 各ドアからの最短距離を求める
    dist = vector<vector<vector<vector<int>>>>(X, vector<vector<vector<int>>>(Y));
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (R[x][y] == 'D') {
                doors.emplace_back(x, y);
                dist[x][y] = bfs(x, y);
            } else if (R[x][y] == '.') {
                ppl.emplace_back(x, y);
            }
        }
    }

    // 二分探索で時刻tを決め、時刻tで全員割当可能か二部マッチングを解く
    int lb = -1, ub = X * Y + 1;
    while (ub - lb > 1) {
        int m = (lb + ub) / 2;
        check(m) ? ub = m : lb = m;
    }
    cout << (ub > X * Y ? "impossible" : to_string(ub)) << endl;
}
