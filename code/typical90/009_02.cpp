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

double get_angle(Point p) {
    double a = p.x / p.abs();
    double angle = acos(a) * 180.0 / M_PI;
    if (p.y >= 0) return angle;
    return 360 - angle;
}

double get_angle2(double i, double j) {
    double res = abs(i - j);
    if (res >= 180) return 360 - res;
    return res;
}

// O(N^2logN)
int main() {
    int n; cin >> n;
    vector<Point> ps(n);
    rep(i, n) cin >> ps[i].x >> ps[i].y;

    double ans = 0;
    rep(i, n) {
        // 偏角ソート
        vector<double> angs;
        rep(j, n) {
            if (j == i) continue;
            Point p = ps[j] - ps[i];
            angs.push_back(get_angle(p));
        }
        sort(angs.begin(), angs.end());
        int m = angs.size();

        // 点Aを全探索して、最も偏角が大きくなる点Cを二分探索
        double res = 0;
        for (auto ang : angs) {
            double t = ang + 180;
            if (t >= 360) t -= 360;
            int pos = lower_bound(angs.begin(), angs.end(), t) - angs.begin();

            int cand1 = pos % m;
            int cand2 = (pos + m - 1) % m;

            double c1 = get_angle2(ang, angs[pos % m]);
            double c2 = get_angle2(ang, angs[(pos + m - 1) % m]);
            res = max({ res, c1, c2});
        }
        ans = max(ans, res);
    }

    cout << fixed << setprecision(9) << ans << endl;
}
