// 探索のメモ化と動的計画法(01ナップサック問題): p52
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// DPは、漸化式とメモ化再帰の2つの捉え方がある
// 漸化式: dp[i+1]をdp[i]などを使って更新していく処理をループで書く
// メモ化再帰: 再帰関数で全探索を描きつつメモ化を書く

// bitDPやゲーム問題などはメモ化再帰が書きやすく、他は基本は漸化式で書く

// DPは
// 状態遷移を記述する側面から逐次問題
// 分割統治法のメモ化版という側面から分割を伴う文字列や数列などの問題
// 本質的にDAGを構築しているという側面からグラフ問題
// など応用範囲は多岐にわたる

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    int W; cin >> W;

    // ナップサックdpは基本+1の項数で初期化する
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] < 0) dp[i + 1][j] = dp[i][j];
            else dp[i + 1][j] = max(dp[i][j - w[i]] + v[i], dp[i][j]);
        }
    }

    cout << dp[n][W] << endl;
}
