// 数値積分: p236
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 空間図形においてスライス断面を考えるのは王道中の王道
// (スライスとはいわゆる変数固定で次元を1つ落とすためのテクニックで平面走査と同じ考え方に立っている)
// -> 最終的に求めるのは体積なので最後は次元を戻す必要がある -> 積分を使う -> 断面をfxで表せれば積分すればOK
// -> 積分する時の注意点は積分したい区間全体でfxは一定かどうか。今回は各頂点をスライス面が通過する前後でfxは変わる
// -> 各頂点から頂点ごとに別々に積分して合計を取れば良い
// -> プログラミングで積分は通常数値積分するので、fxではなくf(a),f(b),f(a+b/2)さえあれば十分

const int INF = 101;

// 多角形をxの値でスライスしたときの幅を求める
double width(const vector<int> &X, const vector<int> &Y, int n, double x) {
    double lb = INF, ub = -INF;
    for (int i = 0; i < n; i++) {
        double x1 = X[i], y1 = Y[i], x2 = X[(i + 1) % n], y2 = Y[(i + 1) % n];
        // i番目の辺と交点を持つか調べる
        // 辺をなす2頂点のx座標x1,x2が、xを跨ぐ必要がある
        if ((x1 - x) * (x2 - x) <= 0 && x1 != x2) {
            // 辺とスライス面の交点の座標を計算
            double y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
            // xが頂点を通る場合を除けば2つ辺が見つかるはず
            lb = min(lb, y);
            ub = max(ub, y);
        }
    }
    return max(0.0, ub - lb);
}

int main() {
    int M, N; cin >> M >> N;
    vector<int> X1(M), Y1(M), X2(N), Z2(N);
    for (int i = 0; i < M; i++) cin >> X1[i] >> Y1[i];
    for (int i = 0; i < N; i++) cin >> X2[i] >> Z2[i];

    // 区間の端点を列挙
    int min1 = *min_element(X1.begin(), X1.end()), max1 = *max_element(X1.begin(), X1.end());
    int min2 = *min_element(X2.begin(), X2.end()), max2 = *max_element(X2.begin(), X2.end());

    vector<int> xs;
    for (int i = 0; i < M; i++) xs.push_back(X1[i]);
    for (int i = 0; i < N; i++) xs.push_back(X2[i]);
    sort(xs.begin(), xs.end());

    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i++) {
        double a = xs[i], b = xs[i + 1], c = (a + b) / 2;
        if (min1 <= c && c <= max1 && min2 <= c && c <= max2) {
            // シンプソンの公式で積分
            double fa = width(X1, Y1, M, a) * width(X2, Z2, N, a);
            double fb = width(X1, Y1, M, b) * width(X2, Z2, N, b);
            double fc = width(X1, Y1, M, c) * width(X2, Z2, N, c);
            res += (b - a) / 6 * (fa + 4 * fc + fb);
        }
    }
    cout << fixed << setprecision(10) << res << endl;
}
