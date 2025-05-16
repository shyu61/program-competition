#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// なぜナップサック問題はdpで解くのか？
// 組合せ最適化問題の内、貪欲法で解けるのは、目的関数とコスト関数が最適化方向に単調である場合
// - 例) 本問題において、「価値が高い方が重さが軽い場合」は価値を最大化しようとする時、重さも最小化されるので方向が一致する
// 貪欲で解けず、方向があり、影響が累積的である場合はdpが選択肢になる。ただし閉路がある、制約が飛び地などの場合はグラフが候補になる

int main() {
    int n, W; cin >> n >> W;
    vector<int> w(n), v(n);
    rep(i, n) cin >> w[i] >> v[i];

    // dp[i][j]:=i個目まで見て、重さをjとする時の最大価値
    vector<ll> dp(W + 1);
    rep(i, n) {
        vector<ll> old(W + 1);
        swap(dp, old);
        rep(j, W + 1) {
            if (j - w[i] >= 0) dp[j] = max(old[j], old[j - w[i]] + v[i]);
            else dp[j] = old[j];
        }
    }
    cout << dp[W] << endl;
}
