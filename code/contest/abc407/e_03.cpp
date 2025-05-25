#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

// 類問: https://atcoder.jp/contests/abc312/tasks/abc312_d

int main() {
    string s; cin >> s;
    int n = s.size();

    vector<mint> dp(n + 1);
    dp[0] = 1;
    rep(i, n) {
        vector<mint> old(n + 1);
        swap(dp, old);
        rep(j, n + 1) {
            if (s[i] != '(' && j + 1 <= n) dp[j] += old[j + 1];
            if (s[i] != ')' && j > 0) dp[j] += old[j - 1];
        }
    }
    cout << dp[0].val() << endl;
}
