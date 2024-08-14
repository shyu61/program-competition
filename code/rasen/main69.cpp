#include <iostream>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0): x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(Point p) { return Point(x * p.x, y * p.y); }

    double norm() { return x * x + y * y; }
};
using Vector = Point;

void solve(Point p1, Vector p1p2, Vector p1p) {
    double ip = p1p.x * p1p2.x + p1p.y * p1p2.y;
    double k = ip / p1p2.norm();

    Point x(k * p1p2.x + p1.x, k * p1p2.y + p1.y);
    cout << fixed << setprecision(8) << x.x << " " << x.y << endl;
}

int main() {
    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    Vector p1p2(p2 - p1);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Point p; cin >> p.x >> p.y;
        Vector p1p(p - p1);

        solve(p1, p1p2, p1p);
    }
}
