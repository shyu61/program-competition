#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// クエリ問題

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    sort(a.begin(), a.end());

    int q; cin >> q;
    while (q--) {
        int b; cin >> b;

        int i = lower_bound(a.begin(), a.end(), b) - a.begin();
        int ans = 0;
        if (i == 0) ans = a[i] - b;
        else if (i >= n) ans = b - a[i - 1];
        else ans = min(a[i] - b, b - a[i - 1]);

        cout << ans << endl;
    }
}
