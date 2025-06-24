#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/agc023/tasks/agc023_a

// 🔷初見でどうやったら解けるか
// 部分列の総和なので累積和を考える。累積和を使いたいので、区間の総和が0を累積和で言い換えられないか考えると、
// 累積和の値が同じであることと同値だとわかる。故に頻度分布を求めれば良い。

// 🔷抑えるべき抽象論は？
// 二項演算: nC2
// - ペアの組み合わせ数計算で使う
// - 計算方法
//   - n*(n-1)/2
//   - 足し込みつつ総和をとる
//     - 自分より前の要素としかペアを組まない数え方になるので重複なく数えられる
// 区間和が0: 累積和が等しい

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    unordered_map<ll, int> mp;
    ll ans = 0;
    rep(i, n + 1) ans += mp[s[i]]++;
    cout << ans << endl;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    unordered_map<ll, int> mp;
    rep(i, n + 1) mp[s[i]]++;

    ll ans = 0;
    for (auto [k, v] : mp) ans += ll(v) * (v - 1) / 2;
    cout << ans << endl;
}
