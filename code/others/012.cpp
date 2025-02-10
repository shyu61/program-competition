// https://atcoder.jp/contests/dp/tasks/dp_j
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 期待値問題

// 方針
// 逐次的な操作により複数の状態を持ち、状態に依存して確率が変化するタイプの問題なのでdpで考える
// 寿司が乗っている皿の枚数によって寿司を減らせる確率が変化するので、状態は寿司が乗っている残り皿数に関する情報を持たせる

// ポイント
// dpの遷移記述の方式
//   1. 到達点への遷移
//     - 順方向にdpテーブルを埋めていく
//   2. 出発点からの遷移
//     - 逆方向にdpテーブルを埋めていく。再帰で書くことが多い
// 遷移に±両方が絡む場合は再帰で書く
// 自己遷移に注意する、dpは必ず立式してから実装する

int main() {
    int n; cin >> n;
    vector<int> a(3);
    rep(i, n) {
        int ai; cin >> ai; ai--;
        a[ai]++;
    }

    vector<vector<vector<double>>> dp(n + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, -1)));
    auto rec = [&](auto rec, int i, int j, int k) -> double {
        if (i + j + k == 0) return 0;
        if (dp[i][j][k] != -1) return dp[i][j][k];
        double res = n;
        if (i > 0) res += rec(rec, i - 1, j + 1, k) * i;
        if (j > 0) res += rec(rec, i, j - 1, k + 1) * j;
        if (k > 0) res += rec(rec, i, j, k - 1) * k;
        return dp[i][j][k] = res / (i + j + k);
    };

    double ans = rec(rec, a[2], a[1], a[0]);
    cout << fixed << setprecision(12) << ans << endl;
}
