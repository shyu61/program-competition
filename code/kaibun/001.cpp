#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc147/tasks/abc147_b

// 回文の中心: (n-1)/2
// - 偶数の場合は左側中心を指す
// - ループは常に中心まで(中心も含む)回せば偶奇で扱いが同じになる

int main() {
    string s; cin >> s;
    int n = s.size();
    int c = (n - 1) / 2;

    int ans = 0;
    rep(i, c + 1) {
        if (s[i] != s[n - i - 1]) ans++;
    }
    cout << ans << endl;
}
