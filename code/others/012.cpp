// https://atcoder.jp/contests/dp/tasks/dp_j
#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 期待値dp問題

// 方針
// 操作で変化するものを考えると、各皿の残り寿司数になる。全部個別管理するのは状態数が爆発するので状態数を減らすことを考える。
// 期待値dpで状態数を減らす最も典型はカテゴリー化。残り寿司数ごとにまとめて考える
// dp[残り個数1][残り個数2][残り個数3] := E[操作回数] とすれば良さそう。Σj(Cj*Pj)は常に1

// ポイント
// - 期待値問題の基本系: `dp[i+1] = Σj(dp[j]*Pj + Cj*Pj)`
//   - dp[j]はjに遷移する全てのパスを考慮した確率1の期待値であり、i+1に遷移するパスとしてjを通る確率は必ずしも1ではない。ゆえにPjをかけて期待値を調整する
//   - Cj*Pjは操作に対する固定コストであり、多くの問題においてΣj(Cj*Pj)=1になる
// - ある状態への遷移が±絡む場合は再帰を使う方が安全

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    int c1 = 0, c2 = 0, c3 = 0;
    for (auto a : A) {
        if (a == 1) c1++;
        if (a == 2) c2++;
        if (a == 3) c3++;
    }

    vector<vector<vector<double>>> dp(N + 2, vector<vector<double>>(N + 2, vector<double>(N + 2, -1)));
    auto rec = [&](auto rec, int i, int j, int k) -> double {
        if (dp[i][j][k] >= 0) return dp[i][j][k];
        int bottom = i + j + k;
        if (bottom == 0) return 0;

        double top = N;
        if (k - 1 >= 0) top += k * rec(rec, i, j + 1, k - 1);
        if (j - 1 >= 0) top += j * rec(rec, i + 1, j - 1, k);
        if (i - 1 >= 0) top += i * rec(rec, i - 1, j, k);
        
        return dp[i][j][k] = top / bottom;
    };

    cout << fixed << setprecision(10) << rec(rec, c1, c2, c3) << endl;
}
