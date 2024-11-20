// modの世界
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 合同式はmodの世界の等式と考える。方程式での"同じ数"の考え方が拡張されていて法の周期で無数に存在する
// 加減乗は方程式と同様に扱えるが、modは整数に限定された世界なので除だけはそのまま扱えない。特別にaと法が互いに素な場合のみ割れる

// 逆元
// 割り算とは逆数をかける操作であり、modの世界ではそれが"逆元"になる。逆元はベズーの等式を解くことで求まり、フェルマーの小定理により高速化できる
// 逆元の存在条件はベズーの等式が解を持つことなので、gcd(a,法)==1であることである(互いに素)

// 連立合同式
// 中国剰余定理を使って連立する全ての合同式を満たすx'を1つの合同式で表現し、ベズーの等式に持ち込むことで求解する
// 法が大きいとき、互いに素な数の積に分解できるなら、それらを使って小さい合同式に分割して考えることができる。RSAなどに応用されている

// 商(n/p)の持つ側面
// - 繰り返し減算の回数
// - n以下でpの整数倍の最大値
// - n以下でpで割れる数の個数 => ある値の因数分解におけるpの指数部分を求めるのに利用される。n!の素因数分解が有名

int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = extgcd(a, b, y, x);
    y -= (a / b) * x;
    return d;
}

int mod_inverse(int a, int m) {
    int x, y;
    extgcd(a, m, x, y);
    return ((x % m) + m) % m;
}

vector<int> fact;  // n<pまでのn! mod p のテーブル
// n!=a*p^e として考える
int mod_fact(int n, int p, int& e) {
    e = 0;
    if (n == 0) return 1;

    // pの倍数部分を計算
    int res = mod_fact(n / p, p, e);
    e += n / p;

    // (p-1)!≡-1なので(p-1)!^(n/p)はn/pの偶奇だけで計算できる
    // a mod pを返却
    // a≡(-1)^(n/p) * (n mod p)! * (1*2*...*n/p) (mod p)
    if (n / p % 2 != 0) return res * (p - fact[n % p]) % p;
    return res * fact[n % p] % p;
}
