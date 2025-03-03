#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// 三分探索 or 微分x二分探索

// 罠
// なし

// ポイント
// 条件なし関数の最適値を求めるには、一峰性があるなら三分探索が有効
// → 微分してf'(x)=0となるxを二分探索することでも求められる

// 微分して二分探索する解法
int main() {
    double p; cin >> p;

    auto f = [&](double x) -> double {
        return x + p / pow(2, x / 1.5);
    };

    auto fp = [&](double x) -> double {
        return 1 - (2 * p * log(2) * pow(2, -2 * x / 3)) / 3;
    };

    auto check = [&](double mid) -> bool {
        return fp(mid) < 0;
    };

    double ok = 0, ng = p + 1;
    rep(i, 100) {
        double mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }
    cout << fixed << setprecision(10) << f(ok) << endl;
}

// 三分探索による解法
int main() {
    double p; cin >> p;

    auto f = [&](double x) -> double {
        return x + p / pow(2, x / 1.5);
    };

    double l = 0, r = p + 1;
    rep(i, 500) {
        double c1 = (l * 2 + r) / 3;
        double c2 = (l + r * 2) / 3;
        f(c1) > f(c2) ? l = c1 : r = c2;
    }

    cout << fixed << setprecision(10) << f(l) << endl;
}
