// 点の内包: 半直線を使う方法
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

const double XMAX = 10000;
vector<Point> polygon;
int n;

bool onSegment(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    Vector a = p - s.p1;
    return equals(cross(a, base), 0) && dot(a, base) >= 0 && a.norm() <= base.norm();
}

bool intersect(Segment edge, Segment pline) {
    Vector edge_base = edge.p2 - edge.p1;
    Vector pline_base = pline.p2 - pline.p1;

    Vector a = edge.p1 - pline.p1;
    Vector b = edge.p2 - pline.p1;

    if (cross(edge_base, pline.p1 - edge.p1) * cross(edge_base, pline.p2 - edge.p1) < 0 &&
    cross(pline_base, a) * cross(pline_base, b) < 0) return true;

    // yが小さい方のみ、頂点を通る場合はカウントする
    if (a.y > b.y) swap(a, b);
    if (equals(cross(pline_base, a), 0) &&
        dot(pline_base, a) > EPS &&  // 半直線なので逆向きは許容しない
        !equals(cross(pline_base, b), 0)) return true;  // 辺に水平なケースは除外
    return false;
}

int solve(Point p) {
    Segment pline(p, Point(XMAX + 1, p.y));
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        Segment edge(polygon[i], polygon[(i + 1) % n]);
        if (onSegment(edge, p)) return 1;
        if (intersect(edge, pline)) cnt++;
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
