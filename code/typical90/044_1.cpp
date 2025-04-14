#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// クエリ問題や逐次問題での各操作でO(n)をO(logn)以下にする方法
// - より粒度の大きい仮想的な情報を操作する: pointerのような概念
// - 相対関係が不変なら端点情報
//   - 相対関係は何を基準に見るかが重要
// - 上記以外は、データ構造を使ってO(logn)にする

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int cnt = 0;
    while (q--) {
        int t, x, y; cin >> t >> x >> y, x--, y--;
        if (t == 1) swap(a[(x - cnt + n) % n], a[(y - cnt + n) % n]);
        else if (t == 2) cnt++;
        else cout << a[(x - cnt + n) % n] << '\n';

        if (cnt >= n) cnt %= n;
    }
}
