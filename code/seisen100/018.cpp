#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    int q; cin >> q;
    vector<int> b(q);
    rep(i, q) cin >> b[i];

    sort(a.begin(), a.end());

    int ans = 0;
    rep(i, q) {
        if (binary_search(a.begin(), a.end(), b[i])) ans++;
    }
    cout << ans << endl;
}
