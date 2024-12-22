// 凸包: p233
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// キャリパー法: 凸多角形に対して、全ての頂点を走査して値を求める必要があるケースで使える
// 動作原理:
// 「ある方向から見たとき、最遠点は法線方向にある」という性質を利用している。
// 1ペアのキャリパーを辺に沿って移動させるとき、キャリパー同士が平行になる(キャリパーが互いに法線方向にある)瞬間で評価がしたい
// そのために、キャリパーを動かすときに平行になりうる法のキャリパーを動かす。凸多角形を反時計回りに走査するとき、凸多角形の性質から
// 必ず反時計回りの角度にキャリパーは動くため、一方のキャリパーから見たときにもう一方のキャリパーが時計回りなら自分を動かし、反時計回りなら相手を動かせば良いことがわかる。
// これは外積の符号により表現できる

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

double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        P.emplace_back(x, y);
    }

    sort(P.begin(), P.end(), compX);
    int k = 0;
    vector<Point> qs(N * 2);
    // 下側凸包
    for (int i = 0; i < N; i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).cross(P[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = P[i];
    }
    // 上側凸包
    for (int i = N - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).cross(P[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = P[i];
    }
    qs.resize(k - 1);
    int n = qs.size();

    // 凸包が潰れている場合は別扱い
    if (n == 2) {
        cout << dist(qs[0], qs[1]) << endl;
        return 0;
    }

    int i = 0, j = 0;
    // 初期はx軸方向に最も遠いペアを求める
    for (int k = 0; k < n; k++) {
        if (!compX(qs[i], qs[k])) i = k;
        if (compX(qs[j], qs[k])) j = k;
    }

    double res = 0;
    int si = i, sj = j;
    // 方向を180度回転させる
    while (i != sj || j != si) {
        res = max(res, dist(qs[i], qs[j]));
        // 辺i-(i+1)の法線方向と辺j-(j+1)の法線方向のどちらを先に向くか判定
        // キャリパーiから見たとき、外積が負 => キャリパーjは時計回り方向にある => キャリパーiを動かせば180度(平行)になる可能性がある
        if ((qs[(i + 1) % n] - qs[i]).cross(qs[(j + 1) % n] - qs[j]) < 0) i = (i + 1) % n;
        else j = (j + 1) % n;
    }

    cout << res << endl;
}
