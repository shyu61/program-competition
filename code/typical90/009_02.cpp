#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 幾何, 組合せ最適化

// ポイント
// 3点を考える場合は、中心の点を固定(全探索)するとよい
// 角度配列について
// - 偏角についての配列にすると良い
//   - 偏角はatan2を使う
// - 二分探索は循環させる(剰余を取る)

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
    double theta = atan2(p.y, p.x);
    if (theta < 0) theta += 2 * M_PI;
    return theta * 180 / M_PI;
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
    // 点Bは全探索
    rep(i, n) {
        // 偏角ソート
        vector<double> ags;
        rep(j, n) {
            if (j == i) continue;
            Point p = ps[j] - ps[i];
            ags.push_back(get_angle(p));
        }
        sort(ags.begin(), ags.end());
        int m = ags.size();

        // 点Aを全探索して、最も偏角が大きくなる点Cを二分探索
        double res = 0;
        for (auto ang : ags) {
            double t = ang + 180;
            if (t >= 360) t -= 360;
            int pos = lower_bound(ags.begin(), ags.end(), t) - ags.begin();
            // 普通の配列の値と違って循環させたいので、配列外参照を除外するのではなく剰余を取る
            double c1 = get_angle2(ang, ags[pos % m]);
            double c2 = get_angle2(ang, ags[(pos + m - 1) % m]);
            res = max({ res, c1, c2 });
        }
        ans = max(ans, res);
    }

    cout << fixed << setprecision(9) << ans << endl;
}
