#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 初見でどうやったら解けるか
// 範囲が小さいaを全探索しつつ重複を除外する方法を考える
// 具体的に重複が起こる組み合わせを2,3個調べれば法則に気付ける

// 抑えるべき抽象論
// double,long doubleの誤差なく扱える範囲は必ず抑える
// double: 整数桁は2^53まで
// long double: 整数桁は2^63まで

int main() {
    ll n; cin >> n;
    ll ans = 0;
    for (int a = 1; a < 64; a++) {
        ll a2 = 1LL << a;
        int b = sqrtl(n / a2);
        // [1,b]で2を素因数に持たないものの個数
        ans += (b + 1) / 2;
    }
    cout << ans << endl;
}
