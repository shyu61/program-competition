// https://atcoder.jp/contests/dp/tasks/dp_i
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<double> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    vector<vector<double>> dp(N + 1, vector<double>(N + 1));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i + 1][j + 1] += dp[i][j] * P[i];
            dp[i + 1][j] += dp[i][j] * (1 - P[i]);
        }
    }

    double sum = 0;
    for (int i = N / 2 + 1; i <= N; i++) sum += dp[N][i];
    cout << fixed << setprecision(10) << sum << endl;
}
