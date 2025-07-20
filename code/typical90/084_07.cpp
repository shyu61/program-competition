#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_D&lang=ja

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int ans = -1e9, mn = a[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, a[i] - mn);
        mn = min(mn, a[i]);
    }
    cout << ans << endl;
}
