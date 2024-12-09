// 平面の分割統治法: p324
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 平面の分割統治法のポイント
// x,yどちらかの軸について分割統治を行うのが一般的
// x軸(逆でも可)について分割統治法で絞り込んで、狭められた探索領域に対してy軸についてナイーブに走査する
// => 平面走査と近い設計思想

// 分割統治法全般のポイント
// rec関数は、前半で再帰的に分割し、後半(帰りがけ)で統治処理を記述し、統治結果をreturnする。
// 殆どは領域を跨がないケースと跨ぐケースの2つを考慮して統治していく

struct Point {
    double x, y;
    bool operator<(const Point& p) const { return x < p.x; };
    Point() {};
};

const double INF = numeric_limits<double>::max();
vector<Point> points;

bool compare_y(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
};

// (1)同じ領域内での最小値
// (2)2領域にまたがるペアの最小値
// merge: min((1), (2))
// 分割はxについてソートしてから行い、統治はyについてソートしてから行う
double rec(int left, int right) {
    int n = right - left;
    if (n <= 1) return INF;
    int mid = (left + right) / 2;
    double x = points[mid].x;
    // 分割 & 統治(1)
    double d = min(rec(left, mid), rec(mid, right));  // (1)
    // yについてマージソート
    inplace_merge(points.begin() + left, points.begin() + mid, points.begin() + right, compare_y);

    vector<Point> b;  // 直線から距離d未満の頂点を入れる
    for (int i = left; i < right; i++) {
        if (fabs(points[i].x - x) >= d) continue;  // xについて条件を満たしたものだけyについて調べる

        // bに入っている頂点を末尾からy座標がd以上になるまで見ていく
        // 一方向ペアのみ考えれば良いので、自身よりyが小さいものに対してのペアを走査する
        // この操作自体はO(n^2)だが、この領域の上界は常に5つになるためO(1)で処理できる
        for (int j = b.size() - 1; j >= 0; j--) {
            // points[i]はb[j]よりも必ず大きく、bの後ろの方が必ずpoints[i]とのy座標の差が小さい
            double dx = points[i].x - b[j].x;
            double dy = points[i].y - b[j].y;
            if (dy >= d) break;  // yがd以上離れているペアは考える必要がない
            d = min(d, sqrt(dx * dx + dy * dy));  // 統治(2)
        }
        b.push_back(points[i]);
    }

    return d;
}

int main() {
    int n; cin >> n;
    points = vector<Point>(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    sort(points.begin(), points.end());  // xについてソート
    cout << rec(0, n) << endl;
}
