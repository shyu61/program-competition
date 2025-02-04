#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using uint = unsigned int;

// ジャンル
// 再帰構造, ツリーdp

int main() {
    int n; string s; cin >> n >> s;
    vector<vector<int>> dp(s.size(), vector<int>(2, 1));
    rep(i, s.size()) dp[i][s[i] - '0'] = 0;

    while (dp.size() > 1) {
        vector<vector<int>> old(dp.size() / 3, vector<int>(2, INF));
        swap(dp, old);

        for (int l = 0; l < old.size(); l += 3) {
            rep(s, 8) {
                int cost = 0;
                rep(i, 3) cost += old[l + i][s >> i & 1];
                int x = popcount(uint(s)) >= 2 ? 1 : 0;
                dp[l / 3][x] = min(dp[l / 3][x], cost);
            }
        }
    }
    int ans = max(dp[0][0], dp[0][1]);
    cout << ans << endl;
}