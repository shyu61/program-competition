// 弾性衝突: p145
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 蟻の衝突問題と全く同様に考えられる
// 衝突はすれ違いに帰着させて考えるとシンプルにモデリングできる
// 本問題や蟻の問題は、"対称性"に注目することが重要。どのボールも互いに対象で一つのボールに対してのみ考えれば良いことがわかる

// 衝突の問題を抽象化すると、すれ違いに帰着させることがポイント。かつ"対称性"注目すること。
// できるだけシンプルにモデリングした後で帳尻を合わせることでうまくいくケースが多い。それは対称性だからである。

// 余事象的に考えた方がいいケースは多い。kが奇数の時にしたから上がると考えるより、余事象的に上から降りると考えると偶数と同様に考えられる。

const double g = 10.0;
int H;

// 時刻Tでのボールの位置
double getPos(int T) {
    if (T < 0) return H;
    double t = sqrt(2 * H / g);
    int k = T / t;
    if (k % 2 == 0) {
        double d = T - k * t;
        return H - g * d * d / 2;
    } else {
        double d = k * t + t - T;
        return H - g * d * d / 2;
    }
}

int main() {
    int N, T; double R;
    cin >> N >> H >> R >> T;
    vector<double> y(N);
    for (int i = 0; i < N; i++) {
        // ボールはすれ違うと考える
        y[i] = getPos(T - i);
    }
    // 簡単のためボールはすれ違うとしたが、実際は順序は変わらないのでソートすればそれがボール順になる
    sort(y.begin(), y.end());
    for (int i = 0; i < N; i++) {
        // ボールの大きさを考える
        cout << fixed << setprecision(2) << y[i] + 2 * R * i / 100.0;  // Rをm変換
        cout << (i == N - 1 ? "\n" : " ");
    }
}
