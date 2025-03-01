#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

const int AMAX = 1e6;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> is(AMAX + 1, -1);
    int ans = n + 1;
    rep(i, n) {
        if (is[a[i]] == -1) is[a[i]] = i;
        else {
            ans = min(ans, i - is[a[i]] + 1);
            is[a[i]] = i;
        }
    }

    if (ans == n + 1) cout << -1 << endl;
    else cout << ans << endl;
}
