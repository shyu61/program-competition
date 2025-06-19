#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// n進数→10進数: Σ(n^i * Si)
// 10進数→n進数: reverse(x%n, (x/n)%n, (x/n/n)%n, ...)

int main() {
    string n; int k; cin >> n >> k;

    while (k--) {
        ll ten = 0;
        for (auto c : n) {
            ten = ten * 8 + int(c - '0');
        }
        string res = "";
        while (ten > 0) {
            int mod = ten % 9;
            if (mod == 8) mod = 5;
            res = char(mod + '0') + res;
            ten /= 9;
        }
        n = res;
    }
    if (n == "") cout << 0 << endl;
    else cout << n << endl;
}
