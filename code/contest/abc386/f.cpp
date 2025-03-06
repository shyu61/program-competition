#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// LCS + 貪欲

// 罠
// 操作は3種類あるが選択すべき操作は貪欲に決定できる点
// LCSが普通に求めたらTLEする点

bool solve() {
    int k; string s, t; cin >> k >> s >> t;
    int n = s.size(), m = t.size();

    if (s == t) return true;
    if (abs(n - m) > k) return false;
    if (n < m) {
        swap(s, t);
        swap(n, m);
    }

    vector<int> dp(m + 1);
    rep(i, n) {
        vector<int> old(m + 1);
        swap(dp, old);
        rep(j, m) {
            if (s[i] == t[j]) dp[j + 1] = old[j] + 1;
            else dp[j + 1] = max(dp[j], old[j + 1]);
        }
    }
    return n - dp[m] <= k;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
