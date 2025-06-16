#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc163/tasks/abc163_c

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n - 1) {
        int x; cin >> x, x--;
        a[x]++;
    }
    rep(i, n) cout << a[i] << '\n';
}
