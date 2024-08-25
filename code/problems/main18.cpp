// D - AtCoder Wallpaper: 解答の実装
// https://atcoder.jp/contests/abc354/tasks/abc354_d
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9;
// 二次元累積和
vector<vector<int>> s{{0, 0, 0}, {0, 2, 3}, {0, 3, 6}, {0, 3, 7}, {0, 4, 8}};

ll f(ll x, ll y) {
    int rx = x % 4; x -= rx;
    int ry = y % 2; y -= ry;

    ll res = x / 4 * y / 2 * s[4][2];
    res += y / 2 * s[rx][2];
    res += x / 4 * s[4][ry];
    res += s[rx][ry];

    return res;
}

int main() {
    // 左下:(a,b), 右上:(c,d)
    ll a, b, c, d; cin >> a >> b >> c >> d;
    a += M; b += M; c += M; d += M;

    ll ans = f(c, d) - f(a, d) - f(c, b) + f(a, b);
    cout << ans << endl;
}
