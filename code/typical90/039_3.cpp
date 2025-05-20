#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// ボトルネックはf(K)部分。これをO(nlogn)程度で事前計算できれば良い
// 約数列挙はO(√n)だが、エラトステネスの篩と同様に考えれば調和級数時間で列挙できる

// 🔷抑えるべき抽象論は？
// 約数と倍数はセットで考える
// 倍数計算は調和級数時間になることが多い

int main() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        // iの倍数jについてa[j]++していく
        for (int j = i; j <= n; j += i) a[j]++;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += ll(i) * a[i];
    }
    cout << ans << endl;
}
