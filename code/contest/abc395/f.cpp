#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 条件1: 判定問題帰着による二分探索
// 条件2: 貪欲

// トラップ
// 解をHとせずにコストとすることで、本質的に求める必要があるものを隠蔽している
// 貪欲に渡す値が1つではない点。一瞬累積的に見えdpを考えてしまう罠
// 二分探索でのオーバーフロー

int main() {
    int n, x; cin >> n >> x;
    vector<int> u(n), d(n);
    rep(i, n) cin >> u[i] >> d[i];

    int hmax = 2e9 + 1;
    rep(i, n) hmax = min(hmax, u[i] + d[i]);

    auto check = [&](int h) -> bool {
        int pmx = h, pmn = 0;
        rep(i, n) {
            int c = u[i] + d[i] - h;
            int mx = u[i] >= c ? d[i] : d[i] - (c - u[i]);
            int mn = max(d[i] - c, 0);

            mx = min(mx, pmx + x);
            mn = max(mn, pmn - x);

            if (mx < pmn - x) return false;
            if (mn > pmx + x) return false;

            pmx = mx; pmn = mn;
        }
        return true;
    };

    ll ok = 0, ng = hmax + 1;
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }

    ll ans = 0;
    rep(i, n) ans += u[i] + d[i] - ok;
    cout << ans << endl;
}
