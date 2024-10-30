// 平均最大化: p132
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 組合せ最適化 x 最大/最小問題 => 全探索,貪欲,DP,グラフ
// 貪欲は試せばうまくいかないことがわかり、グラフも特に構造を活かせそうにないので却下

// DPではない理由
// ぱっと見ナップサック問題なのでDPを検討するのは自然だが、比率問題はDPと相性が悪い。
// 理由は局所最適構造になっておらず、累積的に部分問題を最適化できないから。あくまで全体同士を割り算しないと正しい値が求められない。

// 全探索 x 最大/最小 とくれば二分探索を考える。Σv/Σw = xを取り得るかを十分に大きいxから探索すれば良い
// 比率は扱いにくいので分母を払って考える。今回の問題ではΣは計算できないことに気付く(O(n!))。なのでsigma計算を回避する方法として、
// sigmaをまとめてその内部を独立に考える方法である。最終的には`v[i] - x * w[i]`という価値に重みのペナルティを与えたスコアを導入することで、貪欲に帰着させている。

// ポイント
// 比率最適化問題はDPが使えないケースが多い。その代わりにxと置いて分母を払って考える
// 比率最大化は分母に対するペナルティ構造を導入することで貪欲法に帰着できる。
// sigmaをまとめて内部を独立に扱うことでsigma計算を回避できる。

// 二分探索を検討すべきシーン
// "単調性","境界を求めない","解の範囲がわかっている"

int main() {
    int n, k; cin >> n >> k;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    // [left, right)
    double left = 0, right = 1e10;
    for (int q = 0; q < 100; q++) {
        double mid = (left + right) / 2;

        // 最終的なv/wがmid以上を取り得るか判定
        vector<double> y(n);
        for (int i = 0; i < n; i++) {
            y[i] = v[i] - mid * w[i];
        }
        sort(y.rbegin(), y.rend());
        double sum = 0;
        for (int i = 0; i < k; i++) sum += y[i];

        if (sum >= 0) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(2) << left << endl;
}
