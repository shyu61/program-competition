#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<char, int>;

// https://atcoder.jp/contests/abc136/tasks/abc136_d

int main() {
    string s; cin >> s;
    int n = s.size();
    s += '#';

    vector<P> a;
    int l = 0;
    rep(i, n) {
        if (s[i] != s[i + 1]) {
            a.emplace_back(s[i], i - l + 1);
            l = i + 1;
        }
    }

    vector<int> ans(n);
    int pos = 0;
    for (auto [c, len] : a) {
        int cnt = (len + 1) / 2;
        if (c == 'R') {
            ans[pos + len - 1] += cnt;
            ans[pos + len] += len - cnt;
        } else {
            ans[pos] += cnt;
            ans[pos - 1] += len - cnt;
        }
        pos += len;
    }

    rep(i, n) cout << ans[i] << ' ';
    cout << endl;
}
