#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// (n,k)<=1e6 という条件から、何とかして全探索させる
// combの全探索なので普通にcombを実装すれば良い

// 罠
// (n,k)<=1e6 という条件はあくまで組合せ数であり計算量ではない。(計算量はO(k(n,k)))
// 故にcombを取る時に(n,min(k,n-k))とする必要がある
// 補集合を取る必要がある

// ポイント
// XORの特徴
// - 交換則,結合則が成立する
// - 同じ数で2回xorを取ると元に戻る
//   → 補集合的な操作ができる

int main() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    ll all = 0;
    rep(i, n) all ^= a[i];
    bool flip = k > n - k;
    if (flip) k = n - k;

    ll xo = 0, ans = 0;
    auto comb = [&](auto comb, int k, int s, int d) -> void {
        if (d == k) {
            if (flip) ans = max(ans, all ^ xo);
            else ans = max(ans, xo);
            return;
        }
        for (int i = s; i < n; i++) {
            xo ^= a[i];
            comb(comb, k, i + 1, d + 1);
            xo ^= a[i];
        }
    };
    comb(comb, k, 0, 0);

    cout << ans << endl;
}
