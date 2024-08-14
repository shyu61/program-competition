// 円と直線の交点
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
const double EPS = 1e-10;

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
struct Segment {
    Point p1, p2;
};
using Vector = Point;

struct Cycle {
    Point p;
    double r;
};

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return fabs(a - b) < EPS; }

// ==============================
using Line = Segment;
Point project(Line s, Point p) {
    Vector base(s.p2 - s.p1);
    return s.p1 + base * dot(base, p - s.p1) / base.norm();
}

void print(Point a, Point b) {
    if (a.x > b.x) swap(a, b);
    if (equals(a.x, b.x) && a.y > b.y) swap(a, b);

    cout << fixed << setprecision(8) << a.x << " " << a.y << " " << b.x << " " << b.y << endl;
}

void solve(Cycle c, Line l) {
    Vector base = l.p2 - l.p1;
    Point m = project(l, c.p);
    Vector cm = m - c.p;

    if (equals(cm.abs(), c.r)) {
        print(m, m);
        return;
    }

    double d = sqrt(c.r * c.r - cm.norm());
    // 直線の単位ベクトル
    Vector e = base / base.abs();
    print(m + e * d, m - e * d);
}



int main() {
    Cycle c; cin >> c.p.x >> c.p.y >> c.r;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Line l;
        cin >> l.p1.x >> l.p1.y >> l.p2.x >> l.p2.y;
        solve(c, l);
    }
}
