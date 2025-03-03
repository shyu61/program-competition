#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// gridの既出管理はgridを書き換えてしまうと楽

const vector<int> dh = {1,1,1,0,0,-1,-1,-1}, dw = {1,0,-1,1,-1,1,0,-1};

int main() {
    while (true) {
        int w, h; cin >> w >> h;
        if (w == 0 && h == 0) break;
        vector<vector<int>> mas(h, vector<int>(w));
        rep(i, h) rep(j, w) cin >> mas[i][j];
    
        auto dfs = [&](auto dfs, int i, int j) -> void {
            rep(r, 8) {
                int nh = i + dh[r], nw = j + dw[r];
                if (nh < 0 || nh >= h || nw < 0 || nw >= w) continue;
                if (!mas[nh][nw]) continue;
                mas[nh][nw] = 0;
                dfs(dfs, nh, nw);
            }
        };
    
        int ans = 0;
        rep(i, h) rep(j, w) {
            if (mas[i][j]) {
                ans++;
                dfs(dfs, i, j);
            }
        }
        cout << ans << '\n';
    }
}
