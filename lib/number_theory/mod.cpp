#include <bits/stdc++.h>
using namespace std;

struct Mod {
    int mod;
    vector<int> fact;
    bool is_fact_preped = false;

    Mod(int mod): mod(mod) {}

    int extgcd(int a, int b, int& x, int& y) {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        int d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    }

    // 逆元
    int get_inv(int a, int m) {
        int x, y;
        extgcd(a, m, x, y);
        return ((x % m) + m) % m;
    }

    // 0<=n<p に対しての n! mod p テーブルの事前計算
    void prep_fact() {
        fact = vector<int>(mod);
        fact[0] = 1;
        for (int i = 1; i < mod; i++) fact[i] = fact[i - 1] * i % mod;
        is_fact_preped = true;
    }

    // n!
    int get_fact(int n, int& e) {
        if (!is_fact_preped) prep_fact();
        e = 0;
        if (n == 0) return 1;
        int res = get_fact(n / mod, e);
        e += n / mod;

        if (n / mod % 2 != 0) return res * (mod - fact[n % mod]) % mod;
        return res * fact[n % mod] % mod;
    }

    // nCk
    int get_comb(int n, int k) {
        if (n < 0 || k < 0 || n < k) return 0;
        int e1, e2, e3;
        int a1 = get_fact(n, e1), a2 = get_fact(k, e2), a3 = get_fact(n - k, e3);
        if (e1 > e2 + e3) return 0;
        return a1 * get_inv(a2 * a3 % mod, mod) % mod;
    }
};
