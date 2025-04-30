#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題 + 方向が規定される + 影響が累積的 なのでdpで解く

// 🔷抑えるべき抽象論は？
// 貰うdpと配るdpについて
// - ベースは貰うdpの方が書きやすい
// - 状態iへの遷移は複雑で記述しにくいが、状態iからの遷移は書きやすいケースでは配るdpを使う
//   - 期待値問題などで多い

// 貰うdp
int main() {
    int n; cin >> n;
    vector<int> h(n);
    rep(i, n) cin >> h[i];

    vector<int> dp(n);
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }

    cout << dp[n - 1] << endl;
}

// 配るdp
void chmin(int& a, int b) { a = min(a, b); }

int main() {
    int n; cin >> n;
    vector<int> h(n);
    rep(i, n) cin >> h[i];

    vector<int> dp(n, INF);
    dp[0] = 0;
    rep(i, n - 1) {
        chmin(dp[i + 1], dp[i] + abs(h[i + 1] - h[i]));
        if (i < n - 2) chmin(dp[i + 2], dp[i] + abs(h[i + 2] - h[i]));
    }

    cout << dp[n - 1] << endl;
}
