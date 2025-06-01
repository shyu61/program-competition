#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int M = 46;

// 🔷抑えるべき抽象論は？
// 倍数問題
// - 積なのか和なのかで方針が異なる
//   - 積: 約数とペアで考える
//     - lcm(a,b)=a*b/gcd(a,b)
//     - エラトステネスの篩的に考える場合は、調和級数時間になることが多い
//   - 和: 余りが0と考える
//     - 和をとる各要素の剰余を先に取る

int main() {
    int n; cin >> n;
    vector<int> a(M), b(M), c(M);
    rep(i, n) {
        int v; cin >> v;
        a[v % M]++;
    }
    rep(i, n) {
        int v; cin >> v;
        b[v % M]++;
    }
    rep(i, n) {
        int v; cin >> v;
        c[v % M]++;
    }

    ll ans = 0;
    rep(i, M) rep(j, M) rep(k, M) {
        if ((i + j + k) % M == 0) ans += ll(a[i]) * b[j] * c[k];
    }
    cout << ans << endl;
}
