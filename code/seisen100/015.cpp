#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    int n; cin >> n;
    vector<Point> p(n);
    rep(i, n) cin >> p[i].x >> p[i].y;

    vector<int> a(n);
    rep(i, n) a[i] = i;

    int cnt = 0;
    double ans = 0;
    do {
        cnt++;
        double sum = 0;
        rep(i, n - 1) {
            int dx = p[a[i]].x - p[a[i + 1]].x;
            int dy = p[a[i]].y - p[a[i + 1]].y;
            sum += sqrt(dx * dx + dy * dy);
        }
        ans += sum;
    } while (next_permutation(a.begin(), a.end()));

    ans /= cnt;
    cout << fixed << setprecision(8) << ans << endl;
}
