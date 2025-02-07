#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int MOD = 1e9 + 7;

// 行列累乗による解法: O(B^3logN)

// ポイント
// - dp[i][?] => dp[i+1][?] の遷移の形状が同じ場合は行列累乗の可能性を検討する
//   - 遷移が線形であるかを確認。ほとんどのdpは非線形更新(min/max,その他条件分岐)になっている

using Mat = vector<vector<ll>>;

Mat mul(Mat A, Mat B, int mod) {
    using mtype = typename Mat::value_type::value_type;
    int n = A.size();
    Mat res(n, vector<mtype>(n));
    rep(i, n) rep(j, n) rep(k, n) {
        res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % mod;
    }
    return res;
}

template<typename T>
Mat pow(Mat A, T n, int mod) {
    using mtype = typename Mat::value_type::value_type;
    int sz = A.size();
    Mat res(sz, vector<mtype>(sz));
    rep(i, sz) res[i][i] = 1;
    while (n > 0) {
        if (n & 1) res = mul(res, A, mod);
        A = mul(A, A, mod);
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
            int nx = (10 * r + c[i]) % b;
            // r行目nx列の値は、rからnxへの遷移を表す
            A[r][nx] += 1;
        }
    }

    Mat An = pow(A, n, MOD);
    cout << An[0][0] << endl;
}
