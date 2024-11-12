// 幾何の基本: p225
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double EPS = 1e-10;

// 連結判定: Union-Find,グラフ(dfs,scc分解)

// 内積と外積について
// 内積: x射影であり方向を揃えて大きさのみの掛け算を行う
// 外積: y射影であり方向を垂直に揃えることで方向は常にa,bが張る面積に垂直な方向、大きさはa,bがなす平行四辺形の面積になる
// 内積はx方向に関する判定に、外積はy方向の判定に使える。例) 直線上の判定はy方向のみチェックすれば良いので外積で、かつ端点の間にあることはx方向のチェックなので内積を使う

// 幾何の多くは連立方程式を解く代わりに内積と外積をうまく使って解くことがほとんど。
// 交点は、片方の線分上の任意の点を文字で表現しておき、もう一方の線分上にあるか(外積と内積による演算)で求める
// -> つまりは`判定問題`として扱うということ。これは最小最大問題を二分探索で解くのと同じ発想

struct UnionFind {
    vector<int> par;

    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }

    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);  // 経路圧縮
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        // 常に小さい木を大きい木に結合する
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }
};

struct Point {
    double x, y;
    Point() {};
    Point(double x, double y) : x(x), y(y) {};
    Point operator+(Point p) { return Point(x + p.x, y + p.y); };
    Point operator-(Point p) { return Point(x - p.x, y - p.y); };
    double norm() { return x * x + y * y; };
};
struct Segment {
    Point p1, p2;
    Segment() {};
};
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; };
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; };

int ccw(const Point &a, Point b, Point c) {
    // a: 基準点
    b = b - a, c = c - a;
    if(cross(b, c) > EPS) return 1;    // COUNTER_CLOCKWISE
    if(cross(b, c) < -EPS) return -1;  // CLOCKWISE
    if(dot(b, c) < 0) return 2;        // ONLINE_BACK
    if(b.norm() < c.norm()) return -2; // ONLINE_FRONT
    return 0;                          // ON_SEGMENT
}

bool connected(Segment a, Segment b) {
    return ccw(a.p1, a.p2, b.p1) * ccw(a.p1, a.p2, b.p2) <= 0 &&
        ccw(b.p1, b.p2, a.p1) * ccw(b.p1, b.p2, a.p2) <= 0;
}

int main() {
    int n; cin >> n;
    vector<Segment> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].p1.x >> p[i].p1.y >> p[i].p2.x >> p[i].p2.y;
    }

    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (connected(p[i], p[j])) uf.unite(i, j);
        }
    }

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (uf.same(--a, --b)) cout << "CONNECTED" << endl;
        else cout << "NOT CONNECTED" << endl;
    }
}
