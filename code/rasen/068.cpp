#include <iostream>
using namespace std;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0): x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(Point p) { return Point(x * p.x, y * p.y); }

    int norm(Point p) { return x * p.x + y * p.y; }
};
using Vector = Point;

int solve(Vector vec_a, Vector vec_b) {
    // 内積
    int ip = vec_a.x * vec_b.x + vec_a.y * vec_b.y;
    if (ip == 0) return 1;  // 垂直
    // 外戚
    int op = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    if (op == 0) return 2;  // 平行

    return 0;
}

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Point p0, p1, p2, p3;
        cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        Vector vec_a(p1 - p0), vec_b(p3 - p2);
        cout << solve(vec_a, vec_b) << endl;
    }
}