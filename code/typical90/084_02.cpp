#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc019/tasks/abc019_2

int main() {
    string s; cin >> s;
    int n = s.size();
    s += '#';

    string ans;
    int l = 0;
    rep(i, n) {
        if (s[i] != s[i + 1]) {
            ans += s[i];
            ans += to_string(i - l + 1);
            l = i + 1;
        }
    }
    cout << ans << endl;
}
