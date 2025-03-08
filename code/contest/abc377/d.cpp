#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<int> l(n), r(n);
    rep(i, n) cin >> l[i] >> r[i];

    vector<P> events(n);
    rep(i, n) events[i] = {r[i], l[i]};
    sort(events.begin(), events.end());

    int s = 1; ll ans = 0;
    rep(i, n) {
        auto [rx, lx] = events[i];
        // rxに辿り着いた, 区間を計算してsをlxまで進める
        if (lx < s) continue;
        int d = min(rx, m) - 1 - s + 1;
        if (d > 0) {
            ans += ll(d) * (d - 1) / 2 + d;
        }
        s = lx + 1;
        int d2 = min(rx, m) - 1 - s + 1;
        if (d2 > 0) ans -= ll(d2) * (d2 - 1) / 2 + d2;
        if (s > m) break;
    }
    if (s <= m) {
        int d = m - s + 1;
        ans += ll(d) * (d - 1) / 2 + d;
    }
    cout << ans << endl;
}
