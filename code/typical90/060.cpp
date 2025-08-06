#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題のうち、部分列を最適化する種の問題。この種の問題はLISやLCSなど部分列アルゴリズムを使うことが多い。
// 今回は増加部分列なのでLISを使う。両側から考えれば良い。

int main() {
    int n; cin >> n;
    vector<int> a(n), rev(a);
    rep(i, n) {
        cin >> a[i];
        rev[n - i - 1] = a[i];
    }

    // 両側LIS
    const int INF = n + 1;
    auto f = [&](const vector<int>& c) {
        vector<int> res(n);
        vector<int> dp(n, INF);
        rep(i, n) {
            *lower_bound(dp.begin(), dp.end(), c[i]) = c[i];
            res[i] = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
        }
        return res;
    };

    auto L = f(a);
    auto R = f(rev);

    int ans = 0;
    rep(i, n) {
        ans = max(ans, L[i] + R[n - i - 1] - 1);
    }
    cout << ans << endl;
}
