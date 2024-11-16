#include <bits/stdc++.h>
using namespace std;
using Mat = vector<vector<int>>;

int MOD = 10007;

Mat mul(Mat A, Mat B) {
    Mat res = {{0,0},{0,0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;
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
    int n; cin >> n;
    Mat A(2, vector<int>(2));
    A[0][0] = 1, A[0][1] = 1;
    A[1][0] = 1, A[1][1] = 1;

    A = pow(A, n);

    int res = A[0][0];
    cout << res << endl;
}
