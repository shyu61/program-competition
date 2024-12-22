// 円と円の交点
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
struct Cycle {
    Point c;
    double r;
};
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return fabs(a - b) < EPS; }

// ==============================

void print(Point a, Point b) {
    if (a.x > b.x) swap(a, b);
    if (equals(a.x, b.x) && a.y > b.y) swap(a, b);

    cout << fixed << setprecision(8) << a.x << " " << a.y << " " << b.x << " " << b.y << endl;
}

Point rotate(Point p, double sin, double cos) {
    return Point(p.x * cos - p.y * sin, p.x * sin + p.y * cos);
}

void solve(Cycle c1, Cycle c2) {
    // 中心間のベクトル
    Vector base = c2.c - c1.c;

    // 余弦定理で回転角を求める
    double cos = (c1.r * c1.r + base.norm() - c2.r * c2.r) / (2 * c1.r * base.abs());
    double sin = sqrt(1 - cos * cos);
    // 回転
    Vector a = rotate(base, sin, cos) / base.abs() * c1.r;
    Vector b = rotate(base, -sin, cos) / base.abs() * c1.r;

    print(c1.c + a, c1.c + b);
}



int main() {
    Cycle c1; cin >> c1.c.x >> c1.c.y >> c1.r;
    Cycle c2; cin >> c2.c.x >> c2.c.y >> c2.r;
    solve(c1, c2);
}
