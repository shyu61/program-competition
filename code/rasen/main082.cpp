// 線分交差問題
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
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
    Segment() {}
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};
struct Cycle { Point c; double r; };
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
bool equals(double a, double b) { return fabs(a - b) < EPS; }

// ==============================
const int BOTTOM = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int TOP = 3;
int n;

struct Endpoint {
    Point p;
    int seg, st;
    Endpoint() {}
    Endpoint(Point p, int seg, int st): p(p), seg(seg), st(st) {}

    bool operator<(const Endpoint &ep) const {
        // y座標が小さい順にソート
        if (p.y == ep.p.y) return st < ep.st;
        return p.y < ep.p.y;
    }
};

void solve(vector<Segment> segments, vector<Endpoint> endpoints) {
    set<int> bst;
    int cnt = 0;
    sort(endpoints.begin(), endpoints.end());

    for (int i = 0; i < endpoints.size(); i++) {
        Endpoint ep = endpoints[i];
        if (ep.st == BOTTOM) {
            bst.insert(ep.p.x);
        } else if (ep.st == LEFT) {
            double x1 = segments[ep.seg].p1.x;
            double x2 = segments[ep.seg].p2.x;
            if (x1 > x2) swap(x1, x2);

            set<int>::iterator it_l = bst.lower_bound(x1);
            set<int>::iterator it_u = bst.upper_bound(x2);

            cnt += distance(it_l, it_u);
        } else if (ep.st == TOP) {
            bst.erase(ep.p.x);
        }
    }

    cout << cnt << endl;
}

int main() {
    cin >> n;
    vector<Segment> segments(n);
    vector<Endpoint> endpoints(n * 2);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].p1.x >> segments[i].p1.y >> segments[i].p2.x >> segments[i].p2.y;

        if (segments[i].p1.x == segments[i].p2.x && segments[i].p1.y > segments[i].p2.y) {
            swap(segments[i].p1, segments[i].p2);
        }
        if (segments[i].p1.y == segments[i].p2.y && segments[i].p1.x > segments[i].p2.x) {
            swap(segments[i].p1, segments[i].p2);
        }

        if (segments[i].p1.x == segments[i].p2.x) {
            endpoints[i * 2] = Endpoint(segments[i].p1, i, BOTTOM);
            endpoints[i * 2 + 1] = Endpoint(segments[i].p2, i, TOP);
        } else {
            endpoints[i * 2] = Endpoint(segments[i].p1, i, LEFT);
            endpoints[i * 2 + 1] = Endpoint(segments[i].p2, i, RIGHT);
        }
    }
    solve(segments, endpoints);
}
