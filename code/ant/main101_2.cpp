// 応用問題(Evacuation): p206
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 毎回グラフを作り直してるのは無駄っぽい -> 使い回せないか？ -> 前のマッチング状態から、新たに追加した頂点に関して増加パスがあるかを続きから調べれば良いのでは？
// 「増加パスを続きから調べる」という考え方は、フォードファルカーソンのアルゴリズムの考え方と近い
// また、最大フローを求めた後に容量が増えたときに、新たな最大フローを求めるときも、続きから計算することができる

// これは「増加パス」の性質と言える。最大流の増加パスは逆辺を考えることで、既存のフローを修正する可能性を考慮しているし、
// 二部マッチングの増加パスは、既存のマッチングを辿ることで既存のマッチングを修正する可能性を考慮している。
// つまりこれまで構築されたものを修正する能力を有しているアルゴリズムなので、続きから始めても問題ないのである

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

    int N = X * Y;
    int dsize = doors.size(), psize = ppl.size();
    G = vector<vector<int>>(dsize * N + psize);

    // 予め全てのグラフを作っておく
    // 左側のノード群の内、ループで始点をなめつつ増加パスを探索するが、時刻iでそれ以降の時刻のノードは絶対にマッチングしないことが保証されるので予め全部作成できる
    // 増加パスのdfsを見れば明らかで、右から左への遷移はmatchに含まれるノードにしか遷移しない。つまりまだ始点として探索していない左側のノードは絶対にマッチングしない
    // 二部マッチングは本問題のような順番待ちに代表される、リソース割当問題でよく使われる。つまり最適な値を順次増やしながら探索していくという操作はあるあるであり、
    // この考え方はいろんなところで使える
    for (int i = 0; i < dsize; i++) {
        for (int j = 0; j < psize; j++) {
            int d = dist[doors[i].first][doors[i].second][ppl[j].first][ppl[j].second];
            if (d == -1) continue;
            for (int dt = d; dt <= N; dt++) {
                G[(dt - 1) * dsize + i].push_back(N * dsize + j);
            }
        }
    }

    int num = 0;
    match = vector<int>(dsize * N + psize, -1);
    used = vector<bool>(dsize * N + psize);
    for (int i = 0; i < dsize * N; i++) {
        fill(used.begin(), used.end(), 0);
        // 新たな点iを始点とする増加パスが存在するか確認
        if (dfs(i)) {
            if (++num == psize) {
                cout << i / dsize + 1 << endl;
                return 0;
            }
        }
    }
    cout << "impossible" << endl;
}
