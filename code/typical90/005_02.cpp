#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int MOD = 1e9 + 7;

// ポイント
// - dp[i][?] => dp[i+1][?] の遷移の形状が同じ場合は行列累乗の可能性を検討する
//   - 遷移が線形であるかを確認。ほとんどのdpは非線形更新(min/max,その他条件分岐)になっている

using Mat = vector<vector<ll>>;

Mat mul(Mat A, Mat B) {
    Mat res = {{0,0},{0,0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res[i][j] = res[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

Mat pow(Mat m, int n) {
    Mat res = {{1,0},{0,1}};
    while (n > 0) {
        if (n & 1) res = mul(res, m);
        m = mul(m, m);
        n >>= 1;
    }
    return res;
}

int main() {
    ll n; int b, K; cin >> n >> b >> K;
    vector<int> c(K);
    rep(i, K) cin >> c[i];

    Mat A(b, vector<ll>(b));
    rep(r, b) {
        rep(i, K) {
            int nx = (10 * r + c[K]) % b;
            A[r][nx] = (A[r][nx] + 1) % MOD;
        }
    }

    Mat An = pow(A, n);
    cout << An[0][0] << endl;
}
