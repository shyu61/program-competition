// 行列累乗(Matrix Power Series): p184
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Mat = vector<vector<int>>;

// 行列の級数は、等比数列の場合、漸化式で書くことができ、かつ線形結合型なので行列累乗に落とせる。
// ただ、行列の累乗和が、拡張行列((A,0),(I,I))を使って単一の行列累乗に帰着できることは有名事実として知っておくと良い
// 等比数列の和と考えた場合、(I-A)の逆行列が存在する必要があり、これは所与の条件では保証されていないので今回は不適

// 補足
// Aが逆行列を持つ条件: 正方行列かつ、dat(A)≠0
// 行列式はその行列による変換がベクトル空間に与えるスケーリングや、その行列自身の可逆性などを示す指標として知られる

int M;

Mat mul(Mat A, Mat B) {
    Mat res = vector<vector<int>>(A.size(), vector<int>(A.size()));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            for (int k = 0; k < A.size(); k++) {
                res[i][j] = res[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

Mat pow(Mat A, int n) {
    Mat res = vector<vector<int>>(A.size(), vector<int>(A.size()));
    for (int i = 0; i < res.size(); i++) res[i][i] = 1;
    while (n > 0) {
        if (n & 1) res = mul(res, A);
        A = mul(A, A);
        n >>= 1;
    }
    return res;
}

int main() {
    int n, k; cin >> n >> k >> M;
    Mat A(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    Mat B(n * 2, vector<int>(n * 2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
        B[i + n][i] = B[i + n][i + n] = 1;
    }

    B = pow(B, k + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = B[i + n][j] % M;
            if (i == j) a = (a + M - 1) % M;
            cout << a << " ";
        }
        cout << endl;
    }
}
