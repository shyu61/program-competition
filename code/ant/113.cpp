// Numbers: p239
#include <bits/stdc++.h>
using namespace std;
using Mat = vector<vector<int>>;

// 繰り返し二乗法により累乗計算は間に合うが精度が足りない -> 少数計算を避ける避ける必要がある
// -> なんとかルートを消したい -> ルートを消すと言えば共役数を考える
// -> 共役無理数の漸化式としての性質は有名事実として知っておくべき
// -> 条件分岐がない線形な漸化式ということに気付けば、行列累乗という発想が出てくる

// 共役無理数の性質
// - 和と積は整数になる
// - 互いの累乗の和も整数になる
// - 有理数係数多項式において、一方が解ならもう一方も必ず解になる
// - 漸化式で表現できる

int MOD = 1000;

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
    A[0][0] = 3, A[0][1] = 5;
    A[1][0] = 1, A[1][1] = 3;

    A = pow(A, n);
    int res = A[0][0] * 2 - 1;
    cout << setfill('0') << setw(3) << res % MOD << endl;
}
