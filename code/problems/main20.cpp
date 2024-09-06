// E - Toward 0
// https://atcoder.jp/contests/abc350/tasks/abc350_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, a;
double x, y;
unordered_map<ll, double> dp;

// dp[N]: N <= 10^18 より全部は埋められない。必要な部分だけ埋めるには、ループより再帰の方が書きやすい
// dpテーブルが飛び地になるつまり、sparseならvectorよりmapの方がメモリに優しい

double rec(ll nn) {
    if (dp.count(nn) > 0) return dp[nn];
    double sum = 0;
    for (int b = 2; b <= 6; b++) {
        sum += rec(nn / b) + y;
    }
    sum /= 6;
    // b=1のケースを考慮
    sum += y / 6;
    sum = 6 * sum / 5;
    dp[nn] = min(rec(nn / a) + x, sum);

    return dp[nn];
}

int main() {
    cin >> n >> a >> x >> y;
    dp[0] = 0;

    double ans = rec(n);
    printf("%.10f\n", ans);
}
