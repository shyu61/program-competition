// 漸化式を工夫する(01ナップサック問題その2): p60
#include <bits/stdc++.h>
using namespace std;

// 添字の範囲では計算しきれない(dpテーブルを埋められない)場合の対処法
// 1. 本当にdpテーブルを全部埋める必要があるかチェック(取り得ない値はスキップできる)
// 2. dpの値の範囲が狭いなら添字と値をswapして考える

const int MAX_VI = 100;

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    int W; cin >> W;

    int maxv = MAX_VI * n;
    // vを第2インデックス、dpの値をi番目までの要素で価値jを作る最小のwとする
    vector<vector<int>> dp(n + 1, vector<int>(maxv + 1, W + 1));
    for (int i = 0; i < n; i++) dp[i][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < maxv; j++) {
            dp[i + 1][j] = min(dp[i][j - v[i]] + w[i], dp[i][j]);
        }
    }

    // dp[j]の値がWとなるjを探す
    // 取りうるvは必ずしも連続とは限らないので注意, jは取れなくてもj+1は取れることもある
    for (int i = maxv; i >= 0; i--) {
        if (dp[n][i] <= W) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
