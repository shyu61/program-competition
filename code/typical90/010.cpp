#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 累積和は半開区間: sum[l,r) = s[r]-s[l]

int main() {
    int n; cin >> n;
    vector<int> p1(n), p2(n);
    rep(i, n) {
        int c, p; cin >> c >> p;
        if (c == 1) p1[i] = p;
        else p2[i] = p;
    }

    vector<int> s1(n + 1), s2(n + 1);
    rep(i, n) s1[i + 1] = s1[i] + p1[i];
    rep(i, n) s2[i + 1] = s2[i] + p2[i];

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r; l--;
        cout << s1[r] - s1[l] << ' ' << s2[r] - s2[l] << '\n';
    }
}
