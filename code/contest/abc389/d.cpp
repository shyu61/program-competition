#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 幾何, 内包問題, 格子点

// 方針
// 図形の内包問題は、その図形上の端点を考えるのが定石中の定石。図形をそのまま判定させるのは困難。
// 幾何なので対称性を考慮すると、第一象限のみ考えると(i+0.5,j+0.5)の内包判定のみで良いことがわかる
// x方向に明らかに単調性があるので尺取り法もしくは二分探索でO(R),O(RlogR)で解ける

// ポイント
// - 幾何の問題は2乗計算が多いので安全にllを使っておく(大体cast忘れでoverflowするので)
// - 幾何は対称性, 単調性のオンパレード

int main() {
    ll r; cin >> r;

    auto is_inside = [&](ll x, ll y) {
        x = x * 2 + 1, y = y * 2 + 1;
        return x * x + y * y <= r * r * 4;
    };

    ll x = 0, ans = 0;
    for (ll y = r; y >= 1; y--) {
        while (is_inside(x, y)) x++;
        ans += x;
    }
    cout << ans * 4 + 1 << endl;
}
