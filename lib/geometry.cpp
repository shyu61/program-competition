#include <cmath>
using namespace std;
const double EPS = 1e-10;

struct Point {
    double x, y;

    Point() {}
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
    Segment() {}
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};
struct Cycle { Point c; double r; };

using Vector = Point;
using Line = Segment;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return fabs(a - b) < EPS; }

const int COUNTER_CLOCKWISE = 1;
const int CLOCKWISE = -1;
const int ONLINE_BACK = 2;
const int ONLINE_FRONT = -2;
const int ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2) {
    // p0を基準に判定
    Vector a = p1 - p0;  // 基準線分
    Vector b = p2 - p0;

    if (cross(a, b) > 0) return COUNTER_CLOCKWISE;
    if (cross(a, b) < 0) return CLOCKWISE;
    if (dot(a, b) < 0) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}

// 直線に対して射影した点を返す
Point project(Segment s, Point p) {
    Vector base(s.p2 - s.p1);
    return s.p1 + base * dot(base, p - s.p1) / base.norm();
}

// 直線に対して反射した点を返す
Point reflect(Segment s, Point p) {
    Point m = project(s, p);
    return p + (m - p) * 2.0;
}

// 回転
Point rotate(Point p, double sin, double cos) {
    return Point(p.x * cos - p.y * sin, p.x * sin + p.y * cos);
}
