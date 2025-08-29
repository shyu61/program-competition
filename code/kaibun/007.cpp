#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc237/tasks/abc237_c

bool is_palindrome(string s) {
    string t(s.rbegin(), s.rend());
    return s == t;
}

bool solve() {
    string s; cin >> s;
    int n = s.size();
    
    int l = 0, r = n - 1;
    while (l < n && s[l] == 'a') l++;
    while (r >= 0 && s[r] == 'a') r--;

    int lc = l, rc = n - 1 - r;
    if (lc > rc) return false;

    string c = "";
    rep(i, rc - lc) c += 'a';
    return is_palindrome(c + s);
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
