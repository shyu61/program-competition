#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 最小最大化問題

// 方針
// 二分探索

int main() {
    int n, l, k; cin >> n >> l >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    auto check = [&](int mid) -> bool {
        int cnt = 0, sum = 0;
        for (int i = 0; i < n; i++) {
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

    int lb = 0, ub = l + 1;
    while (ub - lb > 1) {
        int mid = (lb + ub) / 2;
        check(mid) ? lb = mid : ub = mid;
    }
    cout << lb << endl;
}
