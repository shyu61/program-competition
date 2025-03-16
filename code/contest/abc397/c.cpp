#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// unique数を動的に管理したい時 → set or cnt配列

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i], a[i]--;

    vector<int> isl(n), isr(n);
    rep(i, n) isr[a[i]]++;
    
    int l = 0, r = 0, ans = 0;
    rep(i, n) {
        if (isr[i] > 0) r++;
    }

    for (auto ai : a) {
        isl[ai]++;
        isr[ai]--;
        if (isl[ai] == 1) l++;
        if (isr[ai] == 0) r--;
        ans = max(ans, l + r);
    }

    cout << ans << endl;
}
