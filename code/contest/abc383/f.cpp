#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// - ナップサックdp, 組合せ最適化, 数式問題

// 方針
// 典型的な01ナップサックの拡張問題なので、`dp[i個目まで見た時][j円]:=満足度のmax`をベースに考える
// 色数の変化をどう判定するかが問題。ナイーブに集合管理すると2^Nで無理なので、状態数を減らす方針を考える
// 状態数削減の基本アプローチは2択で (1)管理範囲を絞る(2)管理対象を変更する のどちらか。(1)ドミノ敷き詰め問題が典型だが本問題には合わない
// (2)を考え、本質的に遷移判定に必要は情報は何かを考える。集合ではなく"変化"さえtrackできればいいので、色ごとにまとめて処理する方針でいく

// ポイント
// 数列の問題で、並び替えが許容されるケースでは、sortすることで求解できるケースがしばしば
//   - sortの目的は2種類で、(1)単調性の作出, (2)グループ化

int main() {
    int N, X, K; cin >> N >> X >> K;
    vector<tuple<int, int, int>> A(N);
    for (int i = 0; i < N; i++) {
        int p, u, c; cin >> p >> u >> c;
        A[i] = {c, p, u};
    }

    sort(A.begin(), A.end());  // 色番号でsort
    vector<vector<ll>> dp(X + 1, vector<ll>(2)), old(X + 1, vector<ll>(2));
    int cur = -1;
    for (auto [c, p, u] : A) {
        swap(dp, old);

        if (c != cur) {  // 色が切り替わる
            for (int i = 0; i <= X; i++) {
                old[i][0] = max(old[i][0], old[i][1]);
            }
            cur = c;
        }

        for (int i = 0; i <= X; i++) {
            dp[i][0] = old[i][0];
            if (i - p >= 0) {
                dp[i][1] = max(old[i][1], max(old[i - p][0] + u + K, old[i - p][1] + u));
            } else {
                dp[i][1] = old[i][1];
            }
        }
    }

    cout << max(dp[X][0], dp[X][1]) << endl;
}
