#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 全ペア走査系で、ペア生成が間に合わないパターン。数式変形,対称性,主客転倒などが選択肢。
// 絶対値が外れればまとめて計算(対称性)できそう。sortして良いので大小関係を寄せることができるので絶対値が外せる。

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    sort(a.begin(), a.end());

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    ll ans = 0;
    rep(i, n) {
        ans += a[i] * i - s[i];
    }
    cout << ans << endl;
}
