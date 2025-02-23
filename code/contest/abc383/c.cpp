#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ジャンル
// グラフ理論, 距離問題, 多始点bfs

// ポイント
// 多始点bfsは、新たな単一始点があると考え、始点を距離0で全て最初にqueueに入れる
// - nw問題でもよくある考え方で、グラフで単一始点が前提のアルゴリズムは、仮想的な始点を作ることで多始点に拡張できるケースが多い
// dfsは最短性を保証しないので、距離を求めたい時は必ずbfsを使う

vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};

int main() {
    int h, w, d; cin >> h >> w >> d;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    queue<P> que;
    vector<vector<int>> dist(h, vector<int>(w, -1));
    rep(i, h) rep(j, w) {
        if (mas[i][j] == 'H') {
            que.emplace(i, j);
            dist[i][j] = 0;
        }
    }

    int ans = 0;
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        if (dist[x][y] > d) break;
        ans++;
        rep(r, 4) {
            int nx = x + dx[r], ny = y + dy[r];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if (mas[nx][ny] != '.') continue;
            if (dist[nx][ny] != -1) continue;
            que.emplace(nx, ny);
            dist[nx][ny] = dist[x][y] + 1;
        }
    }

    cout << ans << endl;
}
