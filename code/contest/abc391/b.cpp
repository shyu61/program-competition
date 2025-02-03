#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, m; cin >> n >> m;
    vector<string> s(n), t(m);
    rep(i, n) cin >> s[i];
    rep(i, m) cin >> t[i];

    rep(i, n - m + 1) {
        rep(j, n - m + 1) {
            bool ok = true;
            rep(k, m) {
                rep(l, m) {
                    if (s[i + k][j + l] != t[k][l]) ok = false;
                }
            }
            if (ok) {
                cout << i + 1 << ' ' << j + 1 << endl;
                return 0;
            }
        }
    }
}
