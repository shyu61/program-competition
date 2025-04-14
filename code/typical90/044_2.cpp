#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 関連問題: https://atcoder.jp/contests/abc199/tasks/abc199_c

int main() {
    int n, q; string s; cin >> n >> s >> q;
    int n2 = n * 2;

    bool flip = false;
    while (q--) {
        int t, a, b; cin >> t >> a >> b, a--, b--;
        if (t == 1) {
            if (flip) swap(s[(a + n) % n2], s[(b + n) % n2]);
            else swap(s[a], s[b]);
        } else {
            flip ^= 1;
        }
    }

    if (flip) rep(i, n2) cout << s[(n + i) % n2];
    else cout << s;
    cout << endl;
}

// flipをshiftと見た方法
int main() {
    int n, q; string s; cin >> n >> s >> q;
    int n2 = n * 2;

    int cnt = 0;
    while (q--) {
        int t, a, b; cin >> t >> a >> b, a--, b--;
        if (t == 1) {
            swap(s[(a - cnt + n2) % n2], s[(b - cnt + n2) % n2]);
        } else {
            cnt += n;
            cnt %= n2;
        }
    }

    rep(i, n2) cout << s[(cnt + i) % n2];
    cout << endl;
}
