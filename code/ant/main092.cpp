// 行列累乗(Blocks): p182
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 組合せ最適化問題なので、DP/全探索/貪欲法/グラフ/ヒューリスティックあたりを検討する
// -> 状況的にDPか全探索で、全探索は4^Nで無理なのでDPを検討する
// -> DPは遷移を扱うのでとりあえず左から順に塗っていくことを考える
// -> 基本に忠実にナップサックDPを考えつつ、遷移式を記述するために場合分けをしてみる
// -> 遷移式は`何に依存するか`を考える。i地点で条件を満たすかどうかは、i-1地点での赤緑の偶奇をトラックすれば良いことに気付く
// プレーンなDPで間に合わない時は、行列累乗が使えないか考える。

const int M = 10007;

using Mat = vector<vector<int>>;

Mat mul(Mat A, Mat B) {
    Mat res = {{0,0,0},{0,0,0},{0,0,0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % M;
            }
        }
    }
    return res;
}

Mat pow(Mat m, int n) {
    Mat res = {{1,0,0},{0,1,0},{0,0,1}};
    while (n > 0) {
        if (n & 1) res = mul(res, m);
        m = mul(m, m);
        n >>= 1;
    }
    return res;
}

int main() {
    int n; cin >> n;
    Mat res = pow({{2,1,0},{2,2,2},{0,1,2}}, n);
    cout << res[0][0] << endl;
}

// int main() {
//     int n; cin >> n;
//     vector<vector<int>> dp(n + 1, vector<int>(3));
//     dp[0][0] = 1;
//     dp[0][1] = dp[0][2] = 0;
//     for (int i = 0; i < n; i++) {
//         dp[i + 1][0] = 2 * dp[i][0] + dp[i][1];
//         dp[i + 1][1] = 2 * dp[i][0] + 2 * dp[i][1] + 2 * dp[i][2];
//         dp[i + 1][2] = dp[i][1] + 2 * dp[i][2];
//     }

//     cout << dp[n][0] << endl;
// }
