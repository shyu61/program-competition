// デックの利用(個数制限付きナップサック): p302
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 01ナップサック: dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]]+v[i])
// 個数制限なしナップサック: dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]]+v[i]) 自己遷移を書く
// 個数制限付きナップサック: dp[i+1][j] = max{dp[i][(j-k)*W[i]+r]-(j-k)*V[i]}+j*V[i] としてスライド最大化を使う

// ポイント
// 周期性があることがポイント。周期性はスライド処理と相性が良い。周期を考える時は商と剰余に分けて考えるのがセオリー
// -> スライド最大化が使えると予想して式変形していく
// 途中max{dp[i][(j-k)*W[i]+r] + k*V[i] | 0<=k<=Mi}が出てくるが、このmax関数はスライドになってないので、範囲にjをいれる必要があると考える
// -> kをjが含まった形に置き換える -> t := j-k

// スライド最小化の本質
// dequeを使うことにより「各window内での比較コストをまるっと削減する」
// => 区間を平行移動させる変数jと、区間幅(windowサイズ)を司る変数k(これは通常はmin/max関数に対して**ある固定長の範囲を持つ変数**として定義される)が絡むとき、
//    変数kによる計算量に対する寄与をなくしO(j)で計算することができる

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n), m(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i] >> m[i];
    int W; cin >> W;

   vector<int> dp(W + 1);

    for (int i = 0; i < n; ++i) {
        // 剰余でグループ化
        for (int r = 0; r < w[i]; r++) {
            deque<pair<int, int>> deq;
            // 商でループ
            for (int j = 0; j * w[i] + r <= W; j++) {
                // dp[j*w[i]+r] = max{dp[(j-k)*w[i]+r]-(j-k)*v[i] | 0<=k<=m[i]} + j*v[i]
                // => t=j-kとすると、j-m[i]<=t<=j
                // 追加: j番目を常に入れれば良い
                // 削除: j-m[i]より小さくなったら範囲外になるので削除
                int val = dp[j * w[i] + r] - j * v[i];

                while (!deq.empty() && deq.back().first <= val) deq.pop_back();
                deq.emplace_back(val, j);

                dp[j * w[i] + r] = deq.front().first + j * v[i];
                if (deq.front().second == j - m[i]) deq.pop_front();
            }
        }
    }

    cout << dp[W] << endl;
}
