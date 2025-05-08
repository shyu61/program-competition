#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// bの関連問題: https://atcoder.jp/contests/abc197/tasks/abc197_d

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }

    Point rotate(double theta) {
        Point res;
        res.x = x * cos(theta) - y * sin(theta);
        res.y = x * sin(theta) + y * cos(theta);
        return res;
    }
};

int main() {
    int n; cin >> n;
    Point p0, p2n;
    cin >> p0.x >> p0.y >> p2n.x >> p2n.y;
    Point c((p0.x + p2n.x) / 2, double(p0.y + p2n.y) / 2);

    Point ans = p0;
    ans = (ans - c).rotate(2 * M_PI / n) + c;
    cout << fixed << setprecision(10) << ans.x << ' ' << ans.y << endl;
}
