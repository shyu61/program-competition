#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 🔷抑えるべき抽象論は？
// 期待値や確率のdpはバックワード
// - 終端状態で値が確定的になる。構造としてはナップサックdpと逆
// - 制約条件がリソース消費型なのか積み上げ型なのかで判断
// 「期待値は(報酬を考慮した)加重平均である」
// - ある状態は、その遷移先の期待値を加重平均し、遷移による報酬を考慮した値である

int main() {
    int n, x; cin >> n >> x;
    vector<int> scores(n), c(n);
    vector<double> p(n);
    rep(i, n) {
        cin >> scores[i] >> c[i] >> p[i];
        p[i] /= 100;
    }
    int n2 = 1 << n;

    // dp[残りi円][j問目に正解したかの集合]:=最大期待値
    vector<vector<double>> dp(x + 1, vector<double>(n2));
    rep(i, x + 1) rep(s, n2) {
        rep(j, n) {
            if (s >> j & 1) continue;
            if (i - c[j] < 0) continue;
            double now = dp[i - c[j]][s] * (1 - p[j]);
            now += (dp[i - c[j]][s | 1 << j] + scores[j]) * p[j];
            dp[i][s] = max(dp[i][s], now);
        }
    }

    cout << fixed << setprecision(10) << dp[x][0] << endl;
}
