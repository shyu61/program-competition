#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n, p, q; cin >> n >> p >> q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int ans = 0;
    auto dfs = [&](auto dfs, ll prod, int cnt, int d) {
        if (cnt == 5) {
            if (prod % p == q) ans++;
            return;
        }
        if (d == n) return;

        dfs(dfs, prod * a[d] % p, cnt + 1, d + 1);
        dfs(dfs, prod, cnt, d + 1);
    };
    dfs(dfs, 1, 0, 0);
    cout << ans << endl;
}
