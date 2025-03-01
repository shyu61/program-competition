#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 二分探索で「最も近いもの(距離)」を探索する場合は番兵を入れると良い

int main() {
    int D, n, m; cin >> D >> n >> m;
    vector<int> d(n), k(m);
    rep(i, n - 1) cin >> d[i + 1];
    rep(i, m) cin >> k[i];

    sort(d.begin(), d.end());
    d.push_back(D);

    int ans = 0;
    for (auto x : k) {
        int i = lower_bound(d.begin(), d.end(), x) - d.begin();
        if (i > 0) ans += min(d[i] - x, x - d[i - 1]);
        else ans += d[0] - x;
    }
    cout << ans << endl;
}
