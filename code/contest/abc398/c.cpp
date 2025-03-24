#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    map<int, int> cnt;
    rep(i, n) cnt[a[i]]++;

    int ans = -1, mv = -1;
    rep(i, n) {
        if (cnt[a[i]] >= 2) continue;
        if (a[i] > mv) {
            mv = a[i];
            ans = i + 1;
        }
    }
    cout << ans << endl;
}
