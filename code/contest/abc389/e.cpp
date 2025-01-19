#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 方針

int main() {
    int n; ll m; cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    auto f = [&](ll x) -> pair<ll, ll> {
        x--;
        ll num = 0, cost = 0;
        for (auto pi : p) {
            ll k = (x + pi) / (2 * pi);
            if (k > 0 && m / k / k / pi == 0) return {-1, m + 1};  // overflow対策
            num += k;
            cost += k * k * pi;
            if (cost > m) return {-1, m + 1};
        }
        return {num, cost};
    };

    // mid円未満のものを全部買えるか判定
    auto check = [&](ll mid) -> bool { return f(mid).second <= m; };

    ll lb = 1, ub = m + 1;
    while (ub - lb > 1) {
        ll mid = (lb + ub) / 2;
        check(mid) ? lb = mid : ub = mid;
    }

    auto [ans, cost] = f(lb);

    // ちょうどlb円のものを買えるだけ買う
    ans += (m - cost) / lb;
    cout << ans << endl;
}

// ================================================
// TLEするがシンプルな解法

using TL = tuple<ll, ll, int>;
int main() {
    int n; ll m; cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    priority_queue<TL, vector<TL>, greater<TL>> pq;
    for (int i = 0; i < n; i++) pq.emplace(p[i], 1, i);

    ll cost = 0, ans = 0;
    while (!pq.empty()) {
        auto [c, num, i] = pq.top(); pq.pop();
        cost += c;
        if (cost > m) break;
        ans++;
        pq.emplace(p[i] * (2 * num + 1), num + 1, i);
    }
    cout << ans << endl;
}
