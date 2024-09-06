// 反時計回り: 改良版
#include <cmath>
#include <iostream>
#include <iomanip>
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
bool equals(double a, double b) { return (a - b) < EPS; }

// ==============================

Point p0, p1;

string solve(Point p2) {
    Vector a = p1 - p0, b = p2 - p0;
    if (cross(a, b) > 0) return "COUNTER_CLOCKWISE";
    if (cross(a, b) < 0) return "CLOCKWISE";
    if (dot(a, b) < 0) return "ONLINE_BACK";
    if (a.norm() < b.norm()) return "ONLINE_FRONT";
    return "ON_SEGMENT";
}

int main() {
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Point p2; cin >> p2.x >> p2.y;
        cout << solve(p2) << endl;
    }
}
