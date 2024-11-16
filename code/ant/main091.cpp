// 行列累乗(フィボナッチ数列): p180
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// フィボナッチ数列を行列累乗で高速化できる事は知っておくこと
// 一般に、線形結合で表すことができるm項間漸化式は行列累乗で表すことができる。
// そして、左辺の縦ベクトルに対して、右辺の縦ベクトルは1つずれるので、累乗で初項まで戻ることができる

// ***** 行列累乗が使えるシーン *****
// 特定の条件を満たす漸化式に対して適用する。つまりDPとセットで考えるべきで、プレーンなDPで間に合わないとき(nが大きいとき)に使用を検討する
// 1. 漸化式が線形
// 2. 係数が定数
// 3. (基本は)連続項間漸化式
// 4. 遷移に条件分岐がない
//   - 多くのDPの問題は条件分岐がある。逆に条件分岐がない漸化式の場合は行列累乗を使う可能性が高い
// *******************************

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
