// 凸包
#include <algorithm>
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
int n;
vector<Point> polygon;

void andrew() {
    sort(polygon.begin(), polygon.end(), [](Point &p1, Point &p2) {
        if (p1.x == p2.x) return p1.y < p2.y;
        return p1.x < p2.x;
    });

    vector<Point> ans;
    ans.push_back(polygon[0]);
    ans.push_back(polygon[1]);
    // 下側を反時計回りに
    for (int i = 2; i < n; i++) {
        // ans.size() == 1になると、2点になるので必ず凸多角形条件を満たす
        while (ans.size() > 1) {
            int last = ans.size() - 1;
            if (cross(ans[last] - ans[last - 1], polygon[i] - ans[last - 1]) < 0) ans.pop_back();
            else break;
        }
        ans.push_back(polygon[i]);
    }

    // 上側を反時計回りに
    // i=n-1の終端点はすでにansに含まれているのでスキップ
    for (int i = n - 2; i >= 0; i--) {
        while (ans.size() > 1) {
            int last = ans.size() - 1;
            if (cross(ans[last] - ans[last - 1], polygon[i] - ans[last - 1]) < 0) ans.pop_back();
            else break;
        }
        ans.push_back(polygon[i]);
    }
    // 始点と重複するので削除
    ans.pop_back();

    // 開始地点の特定
    int start = 0;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i].y < ans[start].y || (ans[i].y == ans[start].y && ans[i].x < ans[start].x)) {
            start = i;
        }
    }

    // 出力
    int n_vertex = ans.size();
    cout << n_vertex << endl;
    for (int i = start; i < n_vertex + start; i++) {
        cout << ans[i % n_vertex].x << " " << ans[i % n_vertex].y << endl;
    }
}

int main() {
    cin >> n;
    polygon = vector<Point>(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }
    andrew();
}
