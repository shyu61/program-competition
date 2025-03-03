#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 二分探索
// https://x.com/meguru_comp/status/697008509376835584/photo/4
int main() {
    auto check = [&](int mid) -> bool {
        // TODO
    };

    int ok, ng; // TODO
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }
}

// 三分探索
// 二分探索は単調性が必要。三分探索は一峰性(極値が高々1つ)が必要。
int main() {
    auto f = [&](double x) -> double {
        // TODO
    };

    double l, r; // TODO
    rep(i, 500) {
        double c1 = (l * 2 + r) / 3;
        double c2 = (l + r * 2) / 3;
        // 下に凸の場合
        f(c1) > f(c2) ? l = c1 : r = c2;
        // 上に凸の場合
        // f(c1) < f(c2) ? l = c1 : r = c2;
    }
    cout << fixed << setprecision(10) << f(l) << endl;
}
