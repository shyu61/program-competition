#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 想定解
// 貪欲

// 複数同時最適化問題
// - 独立に考えて判定帰着で合わせる
// - 1つを固定する
//   - 扱いにくい方を固定する

int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n), b(n);
        rep(i, n) cin >> a[i];
        rep(i, n) cin >> b[i];
        
        vector<P> c(n);
        rep(i, n) c[i] = {a[i], b[i]};
        sort(c.begin(), c.end());

        priority_queue<int> pq;
        ll bsum = 0, ans = numeric_limits<ll>::max();
        rep(i, n) {
            auto [ai, bi] = c[i];

            bsum += bi;
            pq.push(bi);

            if (i == k - 1) ans = min(ans, ai * bsum);
            if (i >= k) {
                bsum -= pq.top(); pq.pop();
                ans = min(ans, ai * bsum);
            }
        }
        cout << ans << '\n';
    }
}
