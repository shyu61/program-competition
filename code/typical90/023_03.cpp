#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;

vector<int> dx = {1,1,1,0,0,-1,-1,-1}, dy = {1,0,-1,1,-1,1,0,-1};

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    vector<vector<bool>> used(3, vector<bool>(w));
    auto check = [&](int i, int j) -> bool {
        rep(r, 8) {
            int ni = i + dy[r], nj = j + dx[r];
            if (ni < 0 || nj < 0 || nj >= w) continue;
            if (used[ni][nj]) return false;
        }
        return true;
    };

    vector<vector<int>> states(w);
    auto dfs = [&](auto dfs, int pos, int d, int state) -> void {
        int i = pos / w, j = pos % w;
        if (d == w + 1) {
            states[j].push_back(state);
            return;
        }
        dfs(dfs, pos + 1, d + 1, state);  // 置かない場合
        if (check(i, j)) {
            used[i][j] = true;
            dfs(dfs, pos + 1, d + 1, state | 1 << d);  // 置く場合
            used[i][j] = false;
        }
    };

    rep(i, w) dfs(dfs, i, 0, 0);

    auto check2 = [&](int s, int i, int j) -> bool {
        if (i - 1 >= 0 && j - 1 >= 0 && s & 1) return true;
        if (i - 1 >= 0 && s >> 1 & 1) return true;
        if (i - 1 >= 0 && j + 1 < w && s >> 2 & 1) return true;
        if (j - 1 >= 0 && s >> w & 1) return true;
        return false;
    };

    int w2 = 1 << (w + 1);
    vector<mint> dp(w2);
    dp[0] = 1;
    rep(i, h) {
        rep(j, w) {
            vector<mint> old(w2);
            swap(dp, old);
            for (auto s : states[j]) {
                int nx = s >> 1;
                if (mas[i][j] == '#' || check2(s, i, j)) dp[nx] += old[s];
                else {
                    dp[nx | 1 << w] += old[s];
                    dp[nx] += old[s];
                }
            }
        }
    }

    mint ans = 0;
    rep(i, w2) ans += dp[i];
    cout << ans.val() << endl;
}
