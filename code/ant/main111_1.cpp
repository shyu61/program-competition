// 凸包: p233
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// グラハムスキャンは「凸包の連続する2辺は必ず反時計回りの関係にある」という性質を利用し、連続する2辺の外積<=0を評価する方法
// 本問題は凸包の性質を知っている必要がある問題。
// 「最遠点ペアは凸多角形の頂点から選ばれる」という性質を知っているかどうか。また、全てのペアを調べることはできないので、調べる対象をどうやって絞るかを考えるのがスタートになる。

// 凸多角形の性質
// 任意の2点を結ぶ線分は、必ず多角形の内部または境界に完全に含まれる
// 凸多角形の最遠点ペアは、必ず頂点間に存在する
// 凸多角形の各外角は180度未満 => 連続する2辺は時計回りの関係にある

struct Point {
    int x, y;
    Point() {};
    Point(int x, int y) : x(x), y(y) {};
    Point operator-(const Point &a) { return Point(x - a.x, y - a.y); };
    double cross(Point a) { return x * a.y - y * a.x; };
};

vector<Point> P;

bool compX(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        P.emplace_back(x, y);
    }

    sort(P.begin(), P.end(), compX);
    int k = 0;  // 凸包の頂点数
    vector<Point> qs(N * 2);  // 凸包の頂点の集合
    // 下側凸包
    for (int i = 0; i < N; i++) {
        // 連続する2辺の外積<=0ということは、y射影が0以下なので2辺が反時計回りの関係にあることになる
        while (k > 1 && (qs[k - 1] - qs[k - 2]).cross(P[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = P[i];
    }
    // 上側凸包
    // 下側で調べた最後の点N-1の次から始める
    for (int i = N - 2, t = k; i >= 0; i--) {
        // t>kは下側の辺まで戻らないための条件
        while (k > t && (qs[k - 1] - qs[k - 2]).cross(P[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = P[i];
    }
    qs.resize(k - 1);

    double maxv = 0;
    for (int i = 0; i < qs.size(); i++) {
        for (int j = i + 1; j < qs.size(); j++) {
            double dx = qs[i].x - qs[j].x, dy = qs[i].y - qs[j].y;
            maxv = max(maxv, dx * dx + dy * dy);
        }
    }
    cout << maxv << endl;
}
