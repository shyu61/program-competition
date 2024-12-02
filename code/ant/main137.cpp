// デックの利用(個数制限付きナップサック): p302
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 01ナップサック: dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]]+v[i])
// 個数制限なしナップサック: dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]]+v[i]) 自己遷移を書く

// 個数制限ありナップサック:
// プレーンな立式: dp[i+1][j] = max{dp[i][j-kw[i]]+kv[i]|0<=k<=m[i]} : O(m[i]nW)
// -> 個数制限なしナップサックもO(n^2W)からO(nW)にできたので、近い形を持つ個数制限付きナップサックもO(m[i]nW)からO(nW)へ帰着できるのでは？と考える
// -> 問題はdp[i][j-kw[i]](0<=k<=m[i])の部分で、これをkに非依存的に計算したい
// -> 一旦iを固定して考えると、本問題はdp[j'](0<=)
// -> 0<=k<=m[i]より区間連続的であることから、

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n), m(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i] >> m[i];
    int W; cin >> W;

   vector<int> dp(W + 1);

    for (int i = 0; i < n; ++i) {
        // r=j%w[i]でグループ化
        for (int r = 0; r < w[i]; r++) {
            // j=r, r+w[i], r+2w[i], ...
            deque<pair<int, int>> deq;
            // [0,W]を走査: 商jでループ
            for (int j = 0; j * w[i] + r <= W; j++) {
                int val = dp[j * w[i] + r] - j * v[i];

                while (!deq.empty() && deq.back().first <= val) deq.pop_back();
                deq.emplace_back(val, j);

                dp[j * w[i] + r] = deq.front().first + j * v[i];
                if (deq.front().second == j - m[i]) deq.pop_front();
            }
        }
    }

    cout << dp[W] << endl;
}
