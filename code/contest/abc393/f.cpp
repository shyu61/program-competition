#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using P = pair<int, int>;

int main() {
    int n, Q; cin >> n >> Q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    const int M = 2e5;
    vector<vector<P>> qs(M + 1);
    rep(i, Q) {
        int r, x; cin >> r >> x;
        qs[--r].emplace_back(x, i);
    }

    // LISを求めつつクエリを処理する
    vector<int> dp(n, INF), ans(Q);
    rep(i, n) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
        for (auto [x, ix] : qs[i]) {
            // dp[i]<=xとなる最大のiについてi+1が解, 故にupper_boundを取る
            ans[ix] = upper_bound(dp.begin(), dp.end(), x) - dp.begin();
        }
    }

    for (auto x : ans) cout << x << '\n';
}
