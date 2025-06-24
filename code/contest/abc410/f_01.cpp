#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 数え上げの問題で、縦横の全ペア生成が間に合わないケースなので、なんとかして生成せずに数える方法を考える。
// 数式変形、主客転倒、対称性利用、データ構造(累積和やsegtreeなど)が選択肢。2次元を一気に考えるのはしんどいので、
// 2次元問題のセオリーに則り片方固定で考える。領域内の"個数"が欲しいので累積和を考える。
// ここで、1次元なら「個数が等しい <=> 累積和が等しい」ので、2次元グリッドを1次元に圧縮した配列として扱いたいと思いつける。
// 後は列方向の全探索の際にうまく累積性を使いつつ、1次元の累積和配列を計算し、頻度分布を考えれば良い。

// 🔷抑えるべき抽象論は？
// 上限値の積制約下において、計算量が変数非対称の場合はswap処理をすると良い
// - e.g. 今回はH*W<=3e5で、O(H^2*W)なのでH<Wとなるようswapする

int main() {
    int t; cin >> t;
    while (t--) {
        int h, w; cin >> h >> w;
        vector<string> mas(h);
        rep(i, h) cin >> mas[i];
        if (h > w) {
            swap(h, w);
            vector<string> tmp(h, string(w, '.'));
            rep(i, h) rep(j, w) tmp[i][j] = mas[j][i];
            swap(mas, tmp);
        }

        // 行方向に累積和を取る
        vector<vector<int>> s(h, vector<int>(w + 1));
        rep(i, h) rep(j, w) {
            s[i][j + 1] = s[i][j] + (mas[i][j] == '#' ? 1 : -1);
        }

        // 列方向は全探索
        ll ans = 0;
        vector<int> cnt(h * w * 2 + 1);
        rep(si, h) {
            vector<int> a(w + 1, h * w);
            for (int ti = si; ti < h; ti++) {
                rep(i, w + 1) a[i] += s[ti][i];
                rep(i, w + 1) ans += cnt[a[i]]++;
                rep(i, w + 1) cnt[a[i]] = 0;
            }
        }
        cout << ans << '\n';
    }
}
