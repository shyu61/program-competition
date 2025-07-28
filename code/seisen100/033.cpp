#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

const vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    queue<P> que; que.emplace(0, 0);
    vector<vector<int>> dist(h, vector<int>(w, -1));
    dist[0][0] = 0;
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

    if (dist[h - 1][w - 1] == -1) {
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;
    rep(i, h) rep(j, w) {
        if (mas[i][j] == '.') ans++;
    }
    ans -= dist[h - 1][w - 1] + 1;
    cout << ans << endl;
}
