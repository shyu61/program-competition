// 点の内包: 半直線を使わない方法
#include <cmath>
#include <iostream>
#include <vector>
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
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

struct Cycle { Point c; double r; };

using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return fabs(a - b) < EPS; }

// ==============================

vector<Point> polygon;
int n;

int solve(Point p) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        Vector a = polygon[i] - p;
        Vector b = polygon[(i + 1) % n] - p;

        if (a.y > b.y) swap(a, b);
        double det = cross(a, b);

        if (equals(det, 0) && dot(a, b) <= EPS) return 1;
        // yが小さい方のベクトルだけ0を含むようにする
        // 同時にa.yとb.yが共に0の場合を除外している
        if (a.y < EPS && EPS < b.y && det > 0) cnt++;
    }
    return cnt % 2 == 0 ? 0 : 2;
}


int main() {
    cin >> n;
    polygon = vector<Point>(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        Point p; cin >> p.x >> p.y;
        cout << solve(p) << endl;
    }
}
