#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 方針
// 全探索するだけ, 最短距離じゃないのでbfs,dfsではないことに注意

// ポイント
// gridの再訪管理はgrid自体を変更してしまうと楽

const vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};

int main() {
    int h, w, k; cin >> h >> w >> k;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    auto dfs = [&](auto dfs, int x, int y, int d) {
        if (d == k) return 1;
        mas[x][y] = '*';
        int res = 0;
        rep(i, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if (mas[nx][ny] != '.') continue;
            res += dfs(dfs, nx, ny, d + 1);
        }
        mas[x][y] = '.';
        return res;
    };

    int ans = 0;
    rep(i, h) rep(j, w) {
        if (mas[i][j] == '.') ans += dfs(dfs, i, j, 0);
    }
    cout << ans << endl;
}
