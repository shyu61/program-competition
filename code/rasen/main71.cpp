// 距離
#include <algorithm>
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

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return (a - b) < EPS; }

const int COUNTER_CLOCKWISE = 1;
const int CLOCKWISE = -1;
const int ONLINE_BACK = 2;
const int ONLINE_FRONT = -2;
const int ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2) {
    // p0を基準に判定
    Vector a = p1 - p0;
    Vector b = p2 - p0;

    if (cross(a, b) > 0) return COUNTER_CLOCKWISE;
    if (cross(a, b) < 0) return CLOCKWISE;
    if (dot(a, b) < 0) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}


int intersect(Segment s1, Segment s2) {
    return ccw(s1.p1, s1.p2, s2.p1) * ccw(s1.p1, s1.p2, s2.p2) <= 0 &&
        ccw(s2.p1, s2.p2, s1.p1) * ccw(s2.p1, s2.p2, s1.p2) <= 0;
}

// ==============================

// 点と直線の距離: 垂線の長さ
using Line = Segment;
double getDistanceLP(Line l, Point p) {
    Vector base = l.p2 - l.p1;
    return fabs(cross(l.p2 - l.p1, p - l.p1)) / base.abs();
}

// 点と線分の距離
double getDistanceSP(Segment s, Point p) {
    Vector base12 = s.p2 - s.p1;
    Vector base21 = s.p1 - s.p2;

    if (dot(base12, p - s.p1) < 0) return (p - s.p1).abs();
    if (dot(base21, p - s.p2) < 0) return (p - s.p2).abs();
    return getDistanceLP(s, p);
}

double pointSegmentDistance(Segment s, Point p) {
    Vector base1 = s.p2 - s.p1;
    Vector base2 = s.p1 - s.p2;
    Vector a = p - s.p1;
    Vector b = p - s.p2;
    if (dot(base1, a) < 0) return a.abs();
    if (dot(base2, b) < 0) return b.abs();
    return fabs(cross(base1, a)) / base1.abs();
}

double solve(Segment s1, Segment s2) {
    // 交点を持つ場合
    if (intersect(s1, s2)) return 0.0;

    // s1を基準線分とする場合
    double d1 = min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2));
    // s2を基準線分とする場合
    double d2 = min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2));

    return min(d1, d2);
}

int main() {
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Segment s1, s2;
        cin >> s1.p1.x >> s1.p1.y >> s1.p2.x >> s1.p2.y >> s2.p1.x >> s2.p1.y >> s2.p2.x >> s2.p2.y;
        cout << fixed << setprecision(8) << solve(s1, s2) << endl;
    }
}
