// 線分の交差判定: ccwを使った解放
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

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Segment s1, s2;
        cin >> s1.p1.x >> s1.p1.y >> s1.p2.x >> s1.p2.y;
        cin >> s2.p1.x >> s2.p1.y >> s2.p2.x >> s2.p2.y;
        cout << intersect(s1, s2) << endl;
    }
}
