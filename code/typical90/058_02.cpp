#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/abc167/tasks/abc167_d

int main() {
    int n; ll k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i], a[i]--;

    int s = 0;
    if (k <= n) {
        rep(i, k) s = a[s];
        cout << s + 1 << endl;
        return 0;
    }
    rep(i, n) s = a[s];
    k -= n;

    int d = 0;
    vector<bool> seen(n);
    while (!seen[s]) {
        d++;
        seen[s] = true;
        s = a[s];
    }
    k %= d;

    rep(i, k) s = a[s];
    cout << s + 1 << endl;
}
