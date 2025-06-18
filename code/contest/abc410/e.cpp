#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

void chmax(int& a, int b) { a = max(a, b); }

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題。過去の選択に累積的に依存するのでdpを考える
// まずは素直に立式してみる。「dp[i番目まで見た時][体力残りがj][魔力の残りがk]:=true/false」
// これだとO(nhm)でTLE。値がbool値の場合は勿体無いので他の情報に置き換えられないか考える。
// true/false <=> 魔力の残りが0以上 と言い換えられるので、第3添字を省略できる。
// 故に、「dp[i番目まで見た時][体力残りがj]:=魔力の残りのmax」として解く

// 🔷抑えるべき抽象論は？
// dpの高速化
// - 値がbool値の時はもっと多くの情報を載せられる他の情報に変換する

int main() {
    int n, h, m; cin >> n >> h >> m;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];

    // dp[i番目まで見た時][体力残りがj]:=魔力の残りのmax
    vector<vector<int>> dp(n + 1, vector<int>(h + 1, -1));
    rep(i, h + 1) dp[0][i] = m;
    rep(i, n) rep(j, h + 1) {
        // 体力を使う場合
        if (j - a[i] >= 0) chmax(dp[i + 1][j - a[i]], dp[i][j]);
        // 魔力を使う場合
        chmax(dp[i + 1][j], dp[i][j] - b[i]);
    }

    for (int i = n; i >= 0; i--) {
        rep(j, h + 1) {
            if (dp[i][j] >= 0) {
                cout << i << endl;
                return 0;
            }
        }
    }
}
