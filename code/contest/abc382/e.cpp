#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 期待値dp, 確率dp

// 方針
// 期待値問題なのでdpを前提に考える。
// 期待値dpは、操作によって変化するものを状態管理すれば良いので、持ってるレア枚数もしくは、手に入れる必要がある残りのレア枚数とする
// 自身からの遷移の方が書きやすそうなので、dp[手に入れる残りレア枚数]:=E[操作回数] とする。
// 遷移には1パック開封でも各枚数の発生確率が必要なので事前計算しておく

// ポイント
// dpを立式する上での注意点
// - 遷移の方向を考える
//   - 順方向の場合: 現在の情報から未来を更新(配るdp)、あるいは過去の情報から現在を更新(貰うdp)する
//   - 逆方向の場合: 「残り」を考える。未来の状態から現時点の状態を更新する
//     - 期待値dpでは現時点からの遷移先が記述しやすいケースが多いため、逆方向がしばしば使われる

int main() {
    int N, X; cin >> N >> X;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<double> P(N + 1);
    P[0] = 1;
    for (int i = 0; i < N; i++) {
        vector<double> old(N + 1);
        swap(P, old);
        double p = A[i] / 100.0;
        for (int j = 0; j <= i; j++) {
            // ある状態への遷移パスが複数ある場合は、分けて累積で記述すると端点を特別扱いしなくて良い
            P[j] += old[j] * (1 - p);
            P[j + 1] += old[j] * p;
        }
    }

    vector<double> dp(X + 1);
    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= N; j++) {
            dp[i] += dp[max(i - j, 0)] * P[j];
        }
        dp[i] += 1;
        dp[i] /= 1 - P[0];
    }

    cout << fixed << setprecision(10) << dp[X] << endl;
}

// int main(){
//     int N, X; cin >> N >> X;
//     vector<int> A(N);
//     for (int i = 0; i < N; i++) cin >> A[i];

//     vector<double> P(N + 1);
//     P[0] = 1;
//     for (int i = 0; i < N; i++) {
//         vector<double> old(N + 1);
//         swap(P, old);
//         double p = A[i] / 100.0;
//         P[0] = old[0] * (1 - p);
//         for (int j = 0; j <= i; j++) {
//             P[j + 1] = old[j] * p + old[j + 1] * (1 - p);
//         }
//     }

//     vector<double> dp(X + 1);
//     for (int i = 1; i <= X; i++) {
//         for (int j = 1; j <= N; j++) {
//             dp[i] += dp[max(i - j, 0)] * P[j];
//         }
//         dp[i] += 1;
//         dp[i] /= 1 - P[0];
//     }

//     cout << fixed << setprecision(10) << dp[X] << endl;
// }
