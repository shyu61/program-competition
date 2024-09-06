// コイン問題
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 50001;

int n, m;
vector<int> coins;
vector<int> dp;

int solve(int cum) {
    int minv = INF;
    for (int i = 0; i < m; i++) {
        int cur = cum - coins[i];

        if (cur < 0) continue;
        if (cur == 0) return 1;
        if (dp[cur] != -1) {
            minv = min(minv, dp[cur] + 1);
        } else {
            dp[cur] = solve(cur);
            minv = min(minv, dp[cur] + 1);
        }
    }
    return minv;
}

int main() {
    cin >> n >> m;
    coins = vector<int>(m);
    for (int i = 0; i < m; i++) {
        cin >> coins[i];
    }
    dp = vector<int>(INF, -1);
    cout << solve(n) << endl;
}
