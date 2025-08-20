#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc147/tasks/abc147_b

int main() {
    string s; cin >> s;
    int n = s.size();
    int n2 = n / 2;

    int ans = 0;
    rep(i, n2) {
        if (s[i] != s[n - i - 1]) ans++;
    }
    cout << ans << endl;
}
