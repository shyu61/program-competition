#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/agc002/tasks/agc002_a

int solve() {
    ll a, b; cin >> a >> b;
    if (a * b <= 0) return 0;
    if (a > 0) return 1;
    int d = b - a + 1;
    if (d % 2 == 0) return 1;
    return -1;
}

int main() {
    int ans = solve();
    if (ans == 0) cout << "Zero" << endl;
    else if (ans == 1) cout << "Positive" << endl;
    else cout << "Negative" << endl;
}
