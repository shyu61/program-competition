#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint1000000007;

mint pow(mint x, ll n) {
    mint res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int solve() {
    ll n; int k; cin >> n >> k;

    if (n == 1) return mint(k).val();
    if (n == 2) {
        if (k == 1) return 0;
        return (mint(k) * (k - 1)).val();
    }
    if (k < 3) return 0;

    mint ans = mint(k) * (k - 1);
    ans *= pow(mint(k - 2), n - 2);
    return ans.val();
}

int main() {
    cout << solve() << endl;
}
