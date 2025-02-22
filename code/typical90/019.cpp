#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// ジャンル
// 組合せ最適化, 区間除去/縮約問題, 区間dp

// 方針
// 組合せ最適化で全探索や貪欲が厳しそうなのでdpを考える。
// 区間を逐次的に除去していく問題であり、Nが比較的小さいので区間dpを考える
// 区間dpの基本通り[l,r]の両側をmergeできる場合と、それ以外の場所をmergeするケースで遷移を描く
// 偶数この場合しかmergeできないことに注意

// ポイント
// 区間dpが使えるシーン
//   - O(N^2)程度になることが多いので、ある程度Nが小さい必要がある
//   - 区間の除去/縮約など

int main() {
    int n; cin >> n;
    int n2 = n * 2;
    vector<int> a(n2);
    rep(i, n2) cin >> a[i];

    vector<vector<int>> dp(n2, vector<int>(n2, INF));
    for (int i = 0; i < n2; i++) {
        dp[i][i] = 0;
        dp[i][i + 1] = abs(a[i] - a[i + 1]);
    }

    auto rec = [&](auto rec, int l, int r) -> int {
        if (l < 0 || l >= n2 || r < 0 || r >= n2) return INF;
        if (dp[l][r] < INF) return dp[l][r];
        int res = INF;
        res = min(res, rec(rec, l + 1, r - 1) + abs(a[l] - a[r]));
        // [l,r]の区間長は偶数であることを前提に、偶数個ずつ見る
        for (int k = l + 1; k < r; k += 2) {
            res = min(res, rec(rec, l, k) + rec(rec, k + 1, r));
        }
        return dp[l][r] = res;
    };
    rec(rec, 0, n2 - 1);

    cout << dp[0][n2 - 1] << endl;
}
