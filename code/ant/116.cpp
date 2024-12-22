// Watering Plants: p244
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最適化問題だが、最適化するものが2つある: スプリンクラーの位置と半径 -> 2つを同時に最適化するのは複雑すぎるので、片方だけ考えたい
// -> 最適化問題で、直接最適解を求めるアルゴリズムがない場合は二分探索を検討するのがセオリー
// -> 半径は単調性が成立するので二分探索で固定できる -> 探索する各rにおける最適な位置(x,y)において全ての円を含められるかの判定問題に帰着される
// -> 故に求めるのは次の2つ
// (1)中心(x,y)を決める
// (2)中心(x,y)を決めた時、全ての円を囲えたかを判定する
// -> (2)は円の包含関係の不等式を全ての円に対してループすれば良いだけ
// -> (1)はスプリンクラーの円の端にくる円の探索を考える。2円にとってのスプリンクラーの最適な配置とは、2円がスプリンクラーに内接する時である。これは「その2円を含みつつ他の円を囲える能力を最大化したスプリンクラーの置き方」と考えることができる。
//   どの2円がその端にくるのかは全探索すれば良い。加えてもう一方のスプリンクラーはただ1つの円のみを囲ませたほうが良いケースもあるので、そのケースも候補に加えておく。
// -> あとは候補の中から2つ選んで条件を達成できるか調べれば良い

// ポイント
// 円と円の交点の求め方は覚えておく(余弦定理とベクトル分解により求める)
// 最適化するものが複数ある場合は二分探索などで片方を固定することを考える
// 円の配置最適化は内接を考えると良い
// -> 最遠点ペアも内部の点は無関係で凸包の頂点集合のみを考慮すれば良いがこれは、「端が探索空間を決定する」という幾何においてあるあるな考え方を使っている。
// 最適化する集合が1つではなく複数個で固定値の場合は、まずはそれを考えずに各部分集合の候補を列挙した後で、その個数個選ぶといった考え方をすると良い
// -> 最小パスカバーのように部分集合の個数を最適化する問題に適したアルゴリズムもある

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {};
    Point operator+(Point p) { return Point(x + p.x, y + p.y); };
    Point operator-(Point p) { return Point(x - p.x, y - p.y); };
    Point operator*(double k) { return Point(k * x, k * y); }
    Point operator/(double k) { return Point(x / k, y / k); }
    double norm() { return x * x + y * y; };
    double abs() { return sqrt(x * x + y * y); };
};
using Vector = Point;

struct Cycle {
    Point p;
    double r;
    Cycle(Point p, double r) : p(p), r(r) {};
};

const int INF = 1001;
int N;
vector<double> X, Y, R;

// 中心(x,y)半径rの円が囲う集合を求める
ll cover(double x, double y, double r) {
    ll S = 0;
    for (int i = 0; i < N; i++) {
        if (R[i] <= r) {
            double dx = x - X[i], dy = y - Y[i], dr = r - R[i];
            if (dx * dx + dy * dy <= dr * dr) {
                S |= 1LL << i;
            }
        }
    }
    return S;
}

pair<Point, Point> intersect(Cycle c1, Cycle c2) {
    // 中心間ベクトル
    Vector c12 = c2.p - c1.p;
    double d = c12.abs();

    // 円が交差しない場合はスキップ
    if (d > c1.r + c2.r || d < abs(c1.r - c2.r)) {
        return make_pair(Point(INF, INF), Point(INF, INF));
    }

    // 余弦定理
    double r1cos = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * d);
    double r1sin = sqrt(c1.r * c1.r - r1cos * r1cos);

    Vector e12 = c12 / d;  // 単位ベクトル
    Vector n12_ccw(-e12.y, e12.x), n12_cw(e12.y, -e12.x);  // 法線ベクトル

    Vector t1 = c1.p + e12 * r1cos + n12_ccw * r1sin;
    Vector t2 = c1.p + e12 * r1cos + n12_cw * r1sin;
    return make_pair(t1, t2);
}

// 半径rの2円で全ての円を含むことができるか
bool check(double r) {
    vector<ll> cand;  // 1つの円で囲える集合のリスト
    cand.push_back(0);

    // パターンa
    // 全ての円のペアを走査
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (R[i] < r && R[j] < r) {
                Cycle c1(Point(X[i], Y[i]), r - R[i]), c2(Point(X[j], Y[j]), r - R[j]);
                auto [t1, t2] = intersect(c1, c2);
                if (t1.x == INF) continue;

                ll ij = 1LL << i | 1LL << j;
                cand.push_back(cover(t1.x, t1.y, r) | ij);
                cand.push_back(cover(t2.x, t2.y, r) | ij);
            }
        }
    }

    // パターンb
    for (int i = 0; i < N; i++) {
        if (R[i] <= r) {
            cand.push_back(cover(X[i], Y[i], r) | 1LL << i);
        }
    }

    // 円の候補から2つ取り出して全て囲えているか調べる
    for (int i = 0; i < cand.size(); i++) {
        for (int j = i + 1; j < cand.size(); j++) {
            if ((cand[i] | cand[j]) == (1LL << N) - 1) {
                // 候補の内、一つでも全ての円を囲めるものが存在すればOK
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> N;
    X = Y = R = vector<double>(N);
    for (int i = 0; i < N; i++) cin >> X[i] >> Y[i] >> R[i];

    double lb = 0, ub = 1000;
    for (int i = 0; i < 100; i++) {
        double mid = (lb + ub) / 2;
        if (check(mid)) ub = mid;
        else lb = mid;
    }
    cout << fixed << setprecision(3) << ub << endl;
}
