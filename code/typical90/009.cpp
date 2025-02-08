#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 幾何, 組合せ最適化

struct Point {
    ll x, y;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(double k) { return Point(k * x, k * y); }
    Point operator/(double k) { return Point(x / k, y / k); }

    double norm() { return x * x + y * y; }
    double abs() { return sqrt(norm()); }

    double dot(Point a) { return x * a.x + y * a.y; }
    double cross(Point a) { return x * a.y - y * a.x; }
};

// O(N^3)
int main() {
    int n; cin >> n;
    vector<Point> ps(n);
    rep(i, n) cin >> ps[i].x >> ps[i].y;

    // bが中心
    auto calc = [&](Point a, Point b, Point c) -> double {
        Point va = a - b, vb = c - b;
        double cs = va.dot(vb) / sqrt(va.norm() * vb.norm());
        cs = max(-1.0, min(1.0, cs));
        return acos(cs) * 180.0 / M_PI;
    };

    double ans = 0;
    rep(i, n) rep(j, n) rep(k, n) {
        if (i == j || j == k || k == i) continue;
        ans = max(ans, calc(ps[i], ps[j], ps[k]));
    }

    cout << fixed << setprecision(9) << ans << endl;
}
