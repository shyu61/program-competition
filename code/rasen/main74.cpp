// 線分の交差判定
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
struct Segment { Point p1, p2; };
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

// ==============================

bool onSegment(Vector a, Vector b) {
    return cross(a, b) == 0 && dot(a, b) >= 0 && b.norm() < a.norm();
}

bool solve(Segment s1, Segment s2) {
    Vector s1_base = s1.p2 - s1.p1;
    Vector s2_base = s2.p2 - s2.p1;
    if (cross(s1_base, s2.p1 - s1.p1) * cross(s1_base, s2.p2 - s1.p1) < 0 &&
        cross(s2_base, s1.p1 - s2.p1) * cross(s2_base, s1.p2 - s2.p1) < 0)
        return 1;

    if (onSegment(s1_base, s2.p1 - s1.p1) ||
        onSegment(s1_base, s2.p2 - s1.p1) ||
        onSegment(s2_base, s1.p1 - s2.p1) || onSegment(s2_base, s1.p2 - s2.p1))
        return 1;
    return 0;
}

int main() {
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Segment s1, s2;
        cin >> s1.p1.x >> s1.p1.y >> s1.p2.x >> s1.p2.y;
        cin >> s2.p1.x >> s2.p1.y >> s2.p2.x >> s2.p2.y;
        cout << solve(s1, s2) << endl;
    }
}
