#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc159/tasks/abc159_b

bool is_palindrome(string s) {
    string t(s.rbegin(), s.rend());
    return s == t;
}

int main() {
    string s; cin >> s;
    int n = s.size();
    int c = (n - 1) / 2;

    if (is_palindrome(s) && is_palindrome(s.substr(0, c)) && is_palindrome(s.substr(c + 1))) {
        cout << "Yes" << endl;
    } else cout << "No" << endl;
}
