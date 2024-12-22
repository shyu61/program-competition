// 反射
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(double k) { return Point(k * x, k * y); }
    Point operator/(double k) { return Point(x / k, y / k); }

    double norm() { return x * x + y * y; }
    double abs() { return sqrt(norm()); }
};
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

void solve(Point p, Point p1, Vector p1p2) {
    Vector p1p(p - p1);

    Vector p1m = p1p2 * (dot(p1p, p1p2) / p1p2.norm());
    Point ans = p + (p1m - p1p) * 2;

    cout << fixed << setprecision(8) << ans.x << " " << ans.y << endl;
}

int main() {
    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    Vector p1p2(p2 - p1);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Point p; cin >> p.x >> p.y;
        solve(p, p1, p1p2);
    }
}
