#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    int q; cin >> q;
    vector<int> qs(q);
    rep(i, q) cin >> qs[i];

    const int M = 40000;
    vector<bool> ans(M + 1);
    int n2 = 1 << n;
    rep(i, n2) {
        int sum = 0;
        rep(j, n) {
            if (i >> j & 1) sum += a[j];
        }
        ans[sum] = true;
    }

    for (auto qi : qs) {
        cout << (ans[qi] ? "yes" : "no") << '\n';
    }
}
