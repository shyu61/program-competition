#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc320/tasks/abc320_b
// 最長回文連続部分列問題

bool is_palindrome(string s) {
    string t(s.rbegin(), s.rend());
    return t == s;
}

// O(N^3)
int main() {
    string s; cin >> s;
    int n = s.size();

    int ans = 1;
    rep(i, n) rep(j, i) {
        if (is_palindrome(s.substr(j, i - j + 1))) ans = max(ans, i - j + 1);
    }
    cout << ans << endl;
}

// O(N^2)
int main() {
    string s; cin >> s;
    s = '#' + s + '$';
    int n = s.size();

    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        // 奇数長
        int j = 1;
        while (s[i - j] == s[i + j]) j++;
        ans = max(ans, (j - 1) * 2 + 1);

        // 偶数長
        if (s[i] != s[i + 1]) continue;
        j = 1;
        while (s[i - j] == s[i + 1 + j]) j++;
        ans = max(ans, (j - 1) * 2 + 2);
    }
    cout << ans << endl;
}

// O(N)
int main() {
    string s; cin >> s;
    int n = s.size();
    string t = "#";
    rep(i, n) {
        t += s[i];
        t += '#';
    }

    n = t.size();
    vector<int> rad(n);
    int i = 0, d = 0;
    while (i < n) {
        while (d <= i && i + d < n && t[i - d] == t[i + d]) d++;
        rad[i] = d;

        int k = 1;
        while (k <= i && k + rad[i - k] < d) {
            rad[i + k] = rad[i - k];
            k++;
        }
        i += k; d -= k;
    }

    int ans = 0;
    rep(i, n) ans = max(ans, rad[i]);
    cout << ans - 1 << endl;
}
