#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

const vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    int sh, sw; cin >> sh >> sw, sh--, sw--;
    int gh, gw; cin >> gh >> gw, gh--, gw--;
    rep(i, h) cin >> mas[i];

    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<P> que;
    que.emplace(sh, sw);
    dist[sh][sw] = 0;
    while (!que.empty()) {
        auto [i, j] = que.front(); que.pop();
        rep(r, 4) {
            int ni = i + dx[r], nj = j + dy[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != '.') continue;
            if (dist[ni][nj] != -1) continue;
            que.emplace(ni, nj);
            dist[ni][nj] = dist[i][j] + 1;
        }
    }

    cout << dist[gh][gw] << endl;
}
