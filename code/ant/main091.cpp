// 行列累乗(フィボナッチ数列): p180
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// フィボナッチ数列を行列累乗で高速化できる事は知っておくこと
// 一般に、線形結合で表すことができるm項間漸化式は行列累乗で表すことができる。
// そして、左辺の縦ベクトルに対して、右辺の縦ベクトルは1つずれるので、累乗で初項まで戻ることができる

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
    ll n; cin >> n;
    Mat m = pow({{1,1},{1,0}}, n);
    cout << m[1][0] << endl;
}
