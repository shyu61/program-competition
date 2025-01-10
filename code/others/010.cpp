// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
#include <bits/stdc++.h>
using namespace std;

// 配るdpについて
// dp[i] := 最初のi個をみた時の最大価値
// つまりdp[i]のiは「i個目」であって「位置i」ではない。dp[i]が考慮しているのはw[i-1],v[i-1]である
// 故にdp[i+1]への遷移は、dp[i]に対してw[i],v[i]を考慮することで行う
// 初期値として何も考慮しないdp[0]を与える必要がある

int main() {
    int N, W; cin >> N >> W;
    vector<int> v(N), w(N);
    for (int i = 0; i < N; i++) cin >> v[i] >> w[i];

    vector<vector<int>> dp(N + 1, vector<int>(W + 1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
            else dp[i + 1][j] = dp[i][j];
        }
    }
    cout << dp[N][W] << endl;
}
