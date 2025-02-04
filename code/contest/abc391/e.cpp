#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using uint = unsigned int;

// ジャンル
// 再帰構造, ツリーdp, 三分木

// 方針
// 再帰構造なので木で考える。最頻値を変更するコストは子ノードを辿ることで累積的に決定するので、木dpで解けることがわかる
// 木dpはあるノードをflipするコストとすればよく、3つの子ノードの組合せ8通りを全探索すれば良い
// 実際に子ノードの値は予め計算することができ、本来は全探索する必要はないが、8通りで十分小さいので予め木の値を計算しておく必要はない

// ポイント
// 入力から変化の方向を確定させることができるが、このように一般化して計算した方が計算は楽になることが多い

// 二分木
// 最下層: n
// 合計　: 2n-1
// d層  : 2^d
// 子　　: 2i+1,2i+2
// 親　　: (i-1)/2

// 三分木
// 最下層: n
// 合計　: (3n-1)/2
// d層  : 3^d
// 子　　: 3i+1,3i+2,3i+3
// 親　　: (i-1)/3

// x分木
// 最下層: n
// 合計　: (nx-1)/(x-1)
// d層  : x^d
// 子　　: xi+1,xi+2,xi+3,...xi+x
// 親　　: (i-1)/x

// 木は構築せず各階層ごとにbottom-upでdpする方法
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

// 三分木を構築してdfsする方法
int main() {
    int n; string s; cin >> n >> s;
    int n3 = s.size();

    vector<vector<int>> dp((3 * n3 - 1) / 2, vector<int>(2, INF));
    int leaf = (n3 - 1) / 2;
    auto dfs = [&](auto dfs, int v, int c) {
        if (dp[v][c] != INF) return dp[v][c];
        // 葉
        if (v >= leaf) {
            int x = s[v - leaf] - '0';
            return abs(x - c);
        }
        rep(t, 8) {
            int cost = 0;
            rep(i, 3) cost += dfs(dfs, v * 3 + i + 1, t >> i & 1);
            int x = popcount(uint(t)) >= 2 ? 1 : 0;
            dp[v][x] = min(dp[v][x], cost);
        }
        return dp[v][c];
    };

    dfs(dfs, 0, 0);

    int ans = max(dp[0][0], dp[0][1]);
    cout << ans << endl;
}
