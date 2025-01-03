#include <bits/stdc++.h>
using namespace std;

// ポイント
// - グラフの距離の初期値は-1ではなくINFにする
// - 多始点bfsは、新たな単一始点があると考え、始点を距離0で全て最初にqueueに入れる
//   - nw問題でもよくある考え方で、グラフで単一始点が前提のアルゴリズムは、仮想的な始点を作ることで多始点に拡張できるケースが多い
// - dfsは最短性を保証しないので、距離を求めたい時は必ずbfsを使う

const int INF = 1e6 + 1;
const array<int, 4> dx = {1,0,-1,0}, dy = {0,1,0,-1};
int H, W, D;
vector<vector<char>> grid;

int main() {
    cin >> H >> W >> D;
    grid = vector<vector<char>>(H, vector<char>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> grid[i][j];
    }

    vector<vector<int>> dist(H, vector<int>(W, INF));
    queue<pair<int, int>> que;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == 'H') {
                dist[i][j] = 0;
                que.emplace(i, j);
            }
        }
    }

    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        for (int r = 0; r < 4; r++) {
            int nx = x + dx[r], ny = y + dy[r];
            if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '.') {
                if (dist[nx][ny] == INF) {
                    dist[nx][ny] = dist[x][y] + 1;
                    que.emplace(nx, ny);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (dist[i][j] <= D) ans++;
        }
    }
    cout << ans << endl;
}
