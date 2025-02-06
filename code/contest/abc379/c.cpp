#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 逐次問題

// ポイント
// 逐次問題は部分的にバッチ的に処理できないかを考える
//   - そうすると高速化できたり、シンプルにモデリングできたりする
// 与えられた配列がsortされいてるのかどうかは常に確認する
// 配列全体の区間分割問題は、番兵を使うと良い

int main() {
    ll n, m; cin >> n >> m;
    vector<pair<ll, ll>> xa(m);
    rep(i, m) cin >> xa[i].first, xa[i].first--;
    rep(i, m) cin >> xa[i].second;

    sort(xa.begin(), xa.end());

    if (xa[0].first != 0) {
        cout << -1 << endl;
        return 0;
    }

    xa.emplace_back(n, 0);

    ll total = n * (n - 1) / 2, cur = 0;
    rep(i, m + 1) {
        auto [x, a] = xa[i];
        if (i > 0) cur -= x - xa[i - 1].first;
        if (cur < 0) break;
        cur += a;
        total -= x * a;
    }
    if (cur != 0) cout << -1 << endl;
    else cout << total << endl;
}
