// 平面の分割統治法: p324
#include <bits/stdc++.h>
using namespace std;

// 平面走査による解法
// 「x,y同時に考えるのは難しいのでxについてのみ考え、yは線形探索する」という設計は分割統治法と同じ
// ただxについて探索範囲を絞ることで、yでの探索空間が非常に小さくO(1)とみなせることが肝である

// スイープラインは基本的に一つだが、それに補助的な役割を担うラインを使うことがしばしばある。
// その多くは、候補点の制御としての役割を担う

struct Point {
    double x, y;
    bool operator<(const Point& p) const { return x < p.x; };
};

int main() {
    int n; cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    sort(points.begin(), points.end());  // x座標でソート

    double d = numeric_limits<double>::infinity();

    // y方向について保持
    // x方向について距離がdより大きいものは保持しない
    multiset<pair<double,int>> active_set;

    int left = 0; // 補助ライン(候補集合の制御を担う)
    // 走査回数はn, 内部処理はBSTでの挿入/削除, および二分探索なのでO(logn) -> O(nlogn)
    for (int i = 0; i < n; i++) {  // スイープライン
        // x方向にdより離れた点をactive_setから除去
        while (points[i].x - points[left].x > d) {
            active_set.erase({points[left].y, left});
            left++;
        }

        // y座標で ±d の範囲のみ比較する
        auto lb = active_set.lower_bound({points[i].y - d, -1});
        auto ub = active_set.upper_bound({points[i].y + d, INT_MAX});
        for (auto it = lb; it != ub; it++) {  // 線形探索だが分割統治法と同じ理由でO(1)になる
            double dx = points[i].x - points[it->second].x;
            double dy = points[i].y - points[it->second].y;
            d = min(d, sqrt(dx * dx + dy * dy));
        }
        active_set.insert({points[i].y, i});
    }

    cout << d << endl;
}
