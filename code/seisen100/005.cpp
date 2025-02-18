#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ポイント
// 3つ探索対象がある時は、真ん中を固定(全探索)すると良い
// 探索対象が等価かどうかに注意する

int main() {
    int a, b, c, x, y; cin >> a >> b >> c >> x >> y;
    ll ans = numeric_limits<ll>::max();
    rep(i, max(x, y) * 2 + 1) {
        ll cost = c * i;
        cost += a * max(0, x - i / 2);
        cost += b * max(0, y - i / 2);
        ans = min(ans, cost);
    }
    cout << ans << endl;
}
