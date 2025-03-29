#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

void chmin(int& a, int b) { a = min(a, b); }

// 1. 問題を理解する
// 組合せ最適化問題, 制約が小さいから全探索が絡む, どのグループに移動させるか3択を組み合わせる
// 合計/3より、各グループの強さを幾つにしないといけないかは求まるので、これを実現する組み合わせが3つ作れるか判定したい

// 2. 計画を立てる
// グループが2つの場合を考えてみる
// ナップサックdpと問題設定が近い
// - 類題を探せ
//   - ナップサックdp
//   - コイン問題
//   - 割当問題, nwフロー系
//   - 複数同時最適化問題
//     - 一つを固定する → 今回は固定できない
//     - 独立に考えられない
// → 違うのはグループが複数あること。ナップサックdpは山から1グループ選んでいくだけ
// → 複数グループ同時最適化問題に近い
//   - 1つを固定することが典型
//     グループ1に選ぶものを全探索

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];

    int s = 0;
    rep(i, n) s += b[i];
    if (s % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }
    s /= 3;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(s + 1, vector<int>(s + 1, INF)));
    dp[0][0][0] = 0;
    rep(i, n) {
        rep(x, s + 1) rep(y, s + 1) {
            if (a[i] == 1) {
                if (x + b[i] <= s) {
                    chmin(dp[i + 1][x][y], dp[i][x + b[i]][y] + 1);
                    if (y - b[i] >= 0) chmin(dp[i + 1][x][y], dp[i][x + b[i]][y - b[i]] + 1);
                }
            }
            if (a[i] == 2) {
                if (y + b[i] <= s) {
                    chmin(dp[i + 1][x][y], dp[i][x][y + b[i]] + 1);
                    if (x - b[i] >= 0) chmin(dp[i + 1][x][y], dp[i][x - b[i]][y + b[i]] + 1);
                }
            }
            if (a[i] == 3) {
                if (x - b[i] >= 0) chmin(dp[i + 1][x][y], dp[i][x - b[i]][y] + 1);
                if (y - b[i] >= 0) chmin(dp[i + 1][x][y], dp[i][x][y - b[i]] + 1);
            }
            chmin(dp[i + 1][x][y], dp[i][x][y]);
        }
    }

    int ans = -1;
    if (dp[n][s][s] != INF) ans = dp[n][s][s];
    cout << ans << endl;
}
