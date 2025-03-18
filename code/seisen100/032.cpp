#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ポイント
// グリッド問題で明確に上下左右を考える時は特に方向に注意する

// 上下左右
const vector<int> dh = {1,-1,0,0}, dw = {0,0,-1,1};

int main() {
    while (true) {
        int w, h; cin >> w >> h;
        if (w == 0 && h == 0) break;

        vector<vector<vector<int>>> mas(h, vector<vector<int>>(w, vector<int>(4)));
        rep(i, h * 2 - 1) {
            if (i % 2 == 0) {
                // 縦棒
                rep(j, w - 1) {
                    int x; cin >> x;
                    mas[i / 2][j][3] = x;
                    mas[i / 2][j + 1][2] = x;
                }
            } else {
                // 横棒
                rep(j, w) {
                    int x; cin >> x;
                    mas[i / 2][j][0] = x;
                    mas[i / 2 + 1][j][1] = x;
                }
            }
        }
    
        vector<vector<int>> dist(h, vector<int>(w, -1));
        auto bfs = [&](int si, int sj) {
            queue<P> que;
            que.emplace(si, sj);
            dist[si][sj] = 1;
    
            while (!que.empty()) {
                auto [i, j] = que.front(); que.pop();
                rep(r, 4) {
                    int ni = i + dh[r], nj = j + dw[r];
                    if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                    if (mas[i][j][r]) continue;
                    if (dist[ni][nj] != -1) continue;
                    que.emplace(ni, nj);
                    dist[ni][nj] = dist[i][j] + 1;
                }
            }
        };
        bfs(0, 0);

        int ans = dist[h - 1][w - 1];
        if (ans == -1) ans = 0;
        cout << ans << '\n';
    }
}
