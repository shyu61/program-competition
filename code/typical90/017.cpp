#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 数え上げ, 計算幾何

struct Point {
    int s, t;
    bool operator<(const Point& other) { return s < other.s; }
};

int main() {
    int n, m; cin >> n >> m;
    vector<Point> seg(m);
    rep(i, m) {
        int l, r; cin >> l >> r, l--, r--;
        seg[i] = Point{l, r};
    }
    sort(seg.begin(), seg.end());

    auto is_intersect = [&](const Point& a, const Point& b) -> bool {
        return a.s < b.s && b.s < a.t && a.t < b.t;
    };

    // 全ペア走査
    int ans = 0;
    rep(i, m) rep(j, i) {
        if (is_intersect(seg[j], seg[i])) ans++;
    }
    cout << ans << endl;
}
