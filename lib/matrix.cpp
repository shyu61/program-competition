#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using Mat = vector<vector<int>>;

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

const int MOD = 10007;
int main() {
    int n; cin >> n;
    Mat A(2, vector<int>(2));
    A[0][0] = 1, A[0][1] = 1;
    A[1][0] = 1, A[1][1] = 1;

    A = pow(A, n, MOD);
    cout << A[0][0] << endl;
}
