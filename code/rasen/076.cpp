// 線分の交点
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

// ==============================
using Line = Segment;
double getDistanceLP(Line l, Point p) {
    Vector base = l.p2 - l.p1;
    return fabs(cross(l.p2 - l.p1, p - l.p1)) / base.abs();
}

Point intersect(Segment s1, Segment s2) {
    double d1 = getDistanceLP(s1, s2.p1);
    double d2 = getDistanceLP(s1, s2.p2);

    Vector v2 = s2.p2 - s2.p1;
    Vector p1x = v2 * (d1 / (d1 + d2));

    return s2.p1 + p1x;
}

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Segment s1, s2;
        cin >> s1.p1.x >> s1.p1.y >> s1.p2.x >> s1.p2.y;
        cin >> s2.p1.x >> s2.p1.y >> s2.p2.x >> s2.p2.y;

        Point x = intersect(s1, s2);
        cout << fixed << setprecision(8) << x.x << " " << x.y << endl;
    }
}
