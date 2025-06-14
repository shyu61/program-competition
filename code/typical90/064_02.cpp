#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// 区間,領域更新について
// - Lazysegtree,imos法を検討
// - 端点更新のみで処理できないかも検討
//   - 階差数列など新たな数列を定義しておくなど
// 求解する上で必要な最小限の情報を考える
// - 本問題は"値"ではなく"差分値"さえあれば十分 → 階差のみtrackすれば良い

int main() {
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> b(n);
    ll ans = 0;
    rep(i, n - 1) {
        b[i] = a[i + 1] - a[i];
        ans += abs(b[i]);
    }

    while (q--) {
        int l, r, v; cin >> l >> r >> v, l--, r--;
        ll pre = 0, now = 0;
        if (l > 0) {
            pre += abs(b[l - 1]);
            b[l - 1] += v;
            now += abs(b[l - 1]);
        }
        if (r < n - 1) {
            pre += abs(b[r]);
            b[r] -= v;
            now += abs(b[r]);
        }
        ans += now - pre;
        cout << ans << '\n';
    }
}
