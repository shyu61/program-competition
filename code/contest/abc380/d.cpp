#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// ジャンル
// 文字列, 周期性, 反転操作

int main() {
    string s; cin >> s;
    int n = s.size();
    int q; cin >> q;

    auto flip = [&](char c) -> char {
        if (islower(c)) return toupper(c);
        return tolower(c);
    };

    while (q--) {
        ll k; cin >> k; k--;
        int si = k % n;
        ll x = popcount(ull(k / n));
        if (x % 2 == 0) cout << s[si] << ' ';
        else cout << flip(s[si]) << ' ';
    }
    cout << endl;
}
