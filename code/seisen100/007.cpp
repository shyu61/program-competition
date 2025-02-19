#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

int main() {
    int n; cin >> n;
    vector<Point> a(n);
    rep(i, n) cin >> a[i].x >> a[i].y;

    sort(a.begin(), a.end());

    auto is_exist = [&](Point& p) -> bool {
        return binary_search(a.begin(), a.end(), p);
    };

    int ans = 0;
    rep(i, n) rep(j, i) {
        int dx = a[i].x - a[j].x;
        int dy = a[i].y - a[j].y;

        Point p1(a[i].x - dy, a[i].y + dx), p2(a[j].x - dy, a[j].y + dx);
        Point p3(a[i].x + dy, a[i].y - dx), p4(a[j].x + dy, a[j].y - dx);

        if ((is_exist(p1) && is_exist(p2)) || (is_exist(p3) && is_exist(p4))) {
            ans = max(ans, dx * dx + dy * dy);
        }
    }
    cout << ans << endl;
}
