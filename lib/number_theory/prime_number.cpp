#include <bits/stdc++.h>
using namespace std;

// 素数判定: O(√n)
bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// 素数列挙: O(nloglogn)
struct Sieve {
    int n;
    vector<int> is_pn, pn;
    Sieve(int n) : n(n), is_pn(n + 1, true) {
        is_pn[0] = is_pn[1] = false;
        for (int i = 2; i <= n; i++) {
            if (is_pn[i]) {
                pn.push_back(i);
                for (int j = i * 2; j <= n; j += i) {
                    is_pn[j] = false;
                }
            }
        }
    }
};

// [a,b)の素数列挙
struct SegSieve {
    int a, b;
    vector<bool> is_pn, is_pn_sm;
    SegSieve(int a, int b) : a(a), b(b), is_pn(b - a, true), is_pn_sm(sqrt(b), true) {
        for (int i = 2; i * i < b; i++) {
            if (is_pn_sm[i]) {
                for (int j = i * 2; j * j < b; j += i) is_pn_sm[j] = false;  // [2,√b)の篩
                // 切り上げ除算
                for (int j = max(2, (a + i - 1) / i * i); j < b; j += i) is_pn[j - a] = false; // [a,b)の篩
            }
        }
    }
};

// 素因数分解: O(√n)
map<int, int> prime_factor(int n) {
    map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res[i]++;
            n /= i;
        }
    }
    if (n != 1) res[n] = 1;
    return res;
}

// 約数の列挙: O(√n)
vector<int> divisor(int n) {
    vector<int> res;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}
