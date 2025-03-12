#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

const vector<int> dh = {-1,0,1,-1,0,1};
const vector<int> dw_odd = {-1,-1,-1,0,1,0};
const vector<int> dw_even = {0,-1,0,1,1,1};

int main() {
    int w, h; cin >> w >> h;
    vector<vector<int>> mas(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> mas[i][j];

    vector<vector<bool>> seen(h, vector<bool>(w));
    auto bfs = [&](int si, int sj, int val) -> int {
        queue<P> que;
        que.emplace(si, sj);
        seen[si][sj] = true;

        bool surrounded = true;
        int res = 0;
        while (!que.empty()) {
            auto [i, j] = que.front(); que.pop();
            int len = 6;
            rep(r, 6) {
                int ni = i + dh[r];
                int nj = j + (i % 2 ? dw_odd[r] : dw_even[r]);
                if (ni < 0 || ni >= h || nj < 0 || nj >= w) {
                    surrounded = false;
                    continue;
                };
                if (mas[ni][nj] != val) continue;
                len--;
                if (seen[ni][nj]) continue;
                que.emplace(ni, nj);
                seen[ni][nj] = true;
            }
            res += len;
        }
        if (val) return res;
        return surrounded ? res : 0;
    };

    int ans = 0;
    rep(i, h) rep(j, w) {
        if (mas[i][j] == 1 && !seen[i][j]) ans += bfs(i, j, 1);
        if (mas[i][j] == 0 && !seen[i][j]) ans -= bfs(i, j, 0);
    }

    cout << ans << endl;
}
