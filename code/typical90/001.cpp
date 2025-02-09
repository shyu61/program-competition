#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 最小最大化問題

// 方針
// 二分探索

int main() {
    int n, l, k; cin >> n >> l >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    auto is_ok = [&](int mid) -> bool {
        int cnt = 0, sum = 0;
        rep(i, n) {
            if (i == 0) sum += a[i];
            else sum += a[i] - a[i - 1];

            if (sum >= mid) {
                cnt++;
                sum = 0;
            }
            if (cnt >= k) return l - a[i] >= mid;
        }
        return false;
    };

    int ok = 0, ng = l + 1;
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        is_ok(mid) ? ok = mid : ng = mid;
    }
    cout << ok << endl;
}
