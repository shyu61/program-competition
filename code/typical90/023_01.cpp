#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

vector<int> dx = {1,1,1,0,0,-1,-1,-1}, dy = {1,0,-1,1,-1,1,0,-1};

// dfsによる全探索
int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    auto dfs = [&](auto dfs, int i, int j) -> mint {
        if (j == w) return dfs(dfs, i + 1, 0);
        if (i == h) return 1;
        if (mas[i][j] != '.') return dfs(dfs, i, j + 1);

        mint res = 0;
        // 置く場合
        bool ok = true;
        rep(r, 8) {
            int ni = i + dy[r], nj = j + dx[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] == 'x') ok = false;
        }
        if (ok) {
            mas[i][j] = 'x';
            res += dfs(dfs, i, j + 1);
            mas[i][j] = '.';
        }

        // 置かない/置けない場合
        res += dfs(dfs, i, j + 1);
        return res;
    };

    mint ans = dfs(dfs, 0, 0);
    cout << ans.val() << endl;
}

// bit全探索
int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    auto is_valid = [&](int s) -> bool {
        rep(i, h) rep(j, w) {
            int is = i * w + j;
            if (s >> is & 1) {
                if (mas[i][j] == '#') return false;
                rep(r, 8) {
                    int ni = i + dy[r], nj = j + dx[r];
                    if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                    if (s >> (ni * w + nj) & 1) return false;
                }
            }
        }
        return true;
    };

    mint ans = 0;
    ll n2 = 1LL << (h * w);
    rep(i, n2) {
        if (is_valid(i)) ans++;
    }
    cout << ans.val() << endl;
}
