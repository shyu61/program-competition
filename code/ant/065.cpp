// 素数に関する基本的なアルゴリズム(素数判定): p110
#include <bits/stdc++.h>
using namespace std;

// 素数判定: O(√n)
bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// 約数の列挙: O(√n)
vector<int> divisor(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            // i * i == nの時はiとn/1が一致するので入れない
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

// 素因数分解: O(√n)
map<int, int> prime_factor(int n) {
    map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res[i]++;
            n /= i;
        }
    }
    // √nより大きい方の素因数があるということ
    if (n != 1) res[n] = 1;
    return res;
}

int main() {
    int n; cin >> n;

    // 素数判定
    cout << is_prime(n) << endl;

    // 約数の列挙
    vector<int> divisors = divisor(n);
    for (auto v : divisors) cout << v << " ";
    cout << endl;

    // 素因数分解
    map<int, int> factors = prime_factor(n);
    for (auto [k, v] : factors) {
        cout << k << ": " << v << ", ";
    }
    cout << endl;
}
