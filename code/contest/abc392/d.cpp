#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 確率, sparse配列

int main() {
    int n; cin >> n;
    vector<ll> k(n);
    vector<unordered_map<int, ll>> a(n);
    rep(i, n) {
        cin >> k[i];
        rep(j, k[i]) {
            int x; cin >> x;
            a[i][x]++;
        }
    }

    double ans = 0;
    rep(i, n) {
        for (int j = i + 1; j < n; j++) {
            ll res = 0;
            if (a[i].size() < a[j].size()) {
                for (auto [ki, vi] : a[i]) res += vi * a[j][ki];
            } else {
                for (auto [ki, vi] : a[j]) res += vi * a[i][ki];
            }
            ans = max(ans, double(res) / (k[i] * k[j]));
        }
    }

    cout << fixed << setprecision(12) << ans << endl;
}
