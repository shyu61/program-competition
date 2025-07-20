#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

ll mpow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int m, n; cin >> m >> n;
    cout << mpow(m, n, 1000000007) << endl;
}
