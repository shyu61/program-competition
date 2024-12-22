// D - AtCoder Wallpaper: 自分の実装
// https://atcoder.jp/contests/abc354/tasks/abc354_d
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void addArea(ll &xs_even, ll &xs_ood, int x) {
    if ((x % 4 + 4) % 4 == 0) xs_ood -= 1;
    else if ((x % 4 + 4) % 4 == 1) xs_even -= 1, xs_ood -= 2;
    else if ((x % 4 + 4) % 4 == 2)  xs_even -= 2, xs_ood -= 1;
    else xs_even -= 1;
}

int main() {
    // 左下:(a,b), 右上:(c,d)
    int a, b, c, d; cin >> a >> b >> c >> d;
    int yrep = (d - b) / 2;
    int yeven = 0, yood = 0;
    if ((d - b) % 2 != 0) {
        if (d % 2 == 0) yeven = 1;
        else yood = 1;
    }

    int amod = (a % 4 + 4) % 4;
    int a4 = a - amod;
    int cmod = (c % 4 + 4) % 4;
    int c4 = c + (4 - cmod);

    ll xs_even = (c4 - a4);
    ll xs_ood = (c4 - a4);

    for (int x = a4 + 1; x <= a; x++) addArea(xs_even, xs_ood, x);
    for (int x = c + 1; x <= c4; x++) addArea(xs_even, xs_ood, x);

    ll ans = yrep * (xs_even + xs_ood) + yeven * xs_even + yood * xs_ood;
    cout << ans << endl;
}
