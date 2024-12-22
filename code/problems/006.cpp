// D - Palindromic Number
// https://atcoder.jp/contests/abc363/tasks/abc363_d
#include <bits/stdc++.h>
using namespace std;

long long n;

long long power(int x) {
    long long p = 1;
    for (int i = 0; i < x; i++) p *= 10;
    return p;
}

void solve() {
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    n--;

    for (int d = 1;; d++) {
        int x = (d + 1) / 2;
        long long k = 9 * power(x - 1);
        if (n <= k) {
            string S = to_string(power(x - 1) + n - 1);
            S.resize(d, ' ');
            for (int i = x; i < d; i++) S[i] = S[d - 1 - i];
            cout << S << endl;
            return;
        } else {
            n -= k;
        }
    }
}

int main() {
    cin >> n;
    solve();
}
