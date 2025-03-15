#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 距離を求める系の問題は並行移動やswapで計算量を落とせないか検討する

int main() {
    int n, q; cin >> n >> q;

    auto f = [&](int s, int t, int x) -> int {
        if (s > t) swap(s, t);
        if (s < x && x < t) return n - t + s;
        return t - s;
    };

    int ans = 0, l = 1, r = 2;
    rep(i, q) {
        char h; int t; cin >> h >> t;
        if (h == 'L') {
            ans += f(l, t, r);
            l = t;
        } else {
            ans += f(r, t, l);
            r = t;
        }
    }
    cout << ans << endl;
}
