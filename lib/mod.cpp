#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

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
// n! = a*p^e
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

// nCk mod pを求める: O(log_p n)
int mod_comb(int n, int k, int p) {
    if (n < 0 || k < 0 || n < k) return 0;
    int e1, e2, e3;
    int a1 = mod_fact(n, p, e1), a2 = mod_fact(k, p, e2), a3 = mod_fact(n - k, p, e3);
    if (e1 > e2 + e3) return 0;
    return a1 * mod_inverse(a2 * a3 % p, p) % p;
}
