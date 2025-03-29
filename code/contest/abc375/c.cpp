#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 解けなかった理由
// 問題を理解できていなかった
// → 行ってる操作が図形的にどういう意味を持つのかを理解していなかった
// → 適切に図示できていなかった

// ポイント
// 回転操作の座標変換は覚えておく

int main() {
    int n; cin >> n;
    vector<string> mas(n);
    rep(i, n) cin >> mas[i];

    vector<string> ans = mas;
    rep(i, n) rep(j, n) {
        int d = min({i + 1, j + 1, n - i, n - j});
        int ni = i, nj = j;
        rep(_, d % 4) {
            int ti = nj, tj = n - 1 - ni;
            ni = ti, nj = tj;
        }
        ans[ni][nj] = mas[i][j];
    }

    rep(i, n) cout << ans[i] << '\n';
}
