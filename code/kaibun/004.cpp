#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc307/tasks/abc307_b

bool is_palindrome(string s) {
    string t(s.rbegin(), s.rend());
    return t == s;
}

bool solve() {
    int n; cin >> n;
    vector<string> a(n);
    rep(i, n) cin >> a[i];

    rep(i, n) rep(j, i) {
        if (is_palindrome(a[i] + a[j])) return true;
        if (is_palindrome(a[j] + a[i])) return true;
    }
    return false;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
