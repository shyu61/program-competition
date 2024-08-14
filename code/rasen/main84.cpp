// コイン問題: 改
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 50001;
int n, m;

int solve(vector<int> coins) {
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        // j番目までのコインを使う
        for (int j = 0; j < m; j++) {
            if (i - coins[j] < 0) continue;
            dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
    }
    return dp[n];
}

int main() {
    cin >> n >> m;
    vector<int> coins(m);
    for (int i = 0; i < m; i++) {
        cin >> coins[i];
    }
    cout << solve(coins) << endl;
}
