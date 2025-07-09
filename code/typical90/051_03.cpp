#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/arc017/tasks/arc017_3

int main() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    auto f = [&](int n2, int offset = 0) {
        vector<int> c;
        rep(s, 1 << n2) {
            ll sum = 0;
            rep(i, n2) {
                if (s >> i & 1) sum += a[i + offset];
            }
            if (sum <= x) c.push_back(sum);
        }
        sort(c.begin(), c.end());
        return c;
    };

    auto c1 = f(n / 2);
    auto c2 = f(n - n / 2, n / 2);

    int ans = 0;
    for (auto v : c1) {
        ans += upper_bound(c2.begin(), c2.end(), x - v) - lower_bound(c2.begin(), c2.end(), x - v);
    }
    cout << ans << endl;
}
