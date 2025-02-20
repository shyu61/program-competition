#include <cmath>
using namespace std;
const double EPS = 1e-10;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(double k) { return Point(k * x, k * y); }
    Point operator/(double k) { return Point(x / k, y / k); }

    double norm() { return x * x + y * y; }
    double abs() { return sqrt(norm()); }

    double dot(Point a) { return x * a.x + y * a.y; }
    double cross(Point a) { return x * a.y - y * a.x; }
};

struct Segment {
    Point p1, p2;
    Segment() {}
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

struct Cycle { Point c; double r; };

bool equals(double a, double b) { return fabs(a - b) < EPS; }

int ccw(const Point &a, Point b, Point c) {
    // a: 基準点
    b = b - a, c = c - a;
    if (b.cross(c) > EPS) return 1;    // COUNTER_CLOCKWISE
    if (b.cross(c) < -EPS) return -1;  // CLOCKWISE
    if (b.dot(c) < 0) return 2;        // ONLINE_BACK
    if (b.norm() < c.norm()) return -2; // ONLINE_FRONT
    return 0;                          // ON_SEGMENT
}

// 直線に対して射影した点を返す
Point project(Segment s, Point p) {
    Point base(s.p2 - s.p1);
    return s.p1 + base * base.dot(p - s.p1) / base.norm();
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
