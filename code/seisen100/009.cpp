#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 全探索は探索対象を吟味する
// - 移動量を全探索するのではなく、移動の対応を全パターン探索すればいい
// - また逆向きに考えて正解の座標から写真の座標への移動を考えて、その移動距離を全探索しても良い
// - とにかく何を全探索するか？を慎重に考えるのが重要

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
    int m; cin >> m;
    vector<Point> t(m);
    rep(i, m) cin >> t[i].x >> t[i].y;
    int n; cin >> n;
    vector<Point> s(n);
    rep(i, n) cin >> s[i].x >> s[i].y;

    map<Point, int> seen;
    rep(i, n) rep(j, m) {
        // t[j]をs[i]へ移動
        Point p(s[i].x - t[j].x, s[i].y - t[j].y);
        seen[p]++;
    }

    for (auto [k, v] : seen) {
        if (v == m) {
            cout << k.x << ' ' << k.y << endl;
            return 0;
        }
    }
}
