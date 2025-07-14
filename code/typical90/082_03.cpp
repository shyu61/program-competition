#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc190/tasks/abc190_d

// 🔷初見でどうやったら解けるか
// 数え上げ x 数論
// 数論は定式化を考えてみるのが良い。定式化して式変形しつつ、制約条件や整数としての性質,約数,倍数などを駆使して解いていく
// 等差数列の和より立式すると、(A+B)(B-A+1)=2N になる。両辺整数より2Nの約数列挙をしつつ、A,Bが整数になるものを数えれば良い

// 🔷抑えるべき抽象論は？
// 数論は定式化を考える
// - 特に整数問題は、因数分解しつつ約数問題に帰着できないか考える

vector<ll> divisor(ll n) {
    vector<ll> res = {1, n};
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

int main() {
    ll n; cin >> n;

    auto c = divisor(n * 2);
    ll ans = 0;
    for (auto x : c) {
        ll y = n * 2 / x;
        if ((x - y + 1) % 2 == 0 && (x + y - 1) % 2 == 0) ans++;
    }
    cout << ans << endl;
}

int main() {
    ll n; cin >> n;

    auto c = divisor(n * 2);
    ll ans = 0;
    for (auto x : c) {
        ll d = n * 2 / x;
        if ((x - d + 1) % 2 == 0) {
            ans++;
        }
    }
    cout << ans << endl;
}
