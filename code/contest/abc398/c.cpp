#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    map<int, int> cnt;
    rep(i, n) cnt[a[i]]++;

    int ans = -1;
    for (auto [k, v] : cnt) {
        if (v >= 2) continue;
        ans = max(ans, k);
    }
    if (ans == -1) {
        cout << ans << endl;
        return 0;
    }
    rep(i, n) {
        if (a[i] == ans) {
            cout << i + 1 << endl;
            return 0;
        }
    }
}
