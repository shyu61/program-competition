#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, m; cin >> n >> m;
    vector<int> k(m);
    vector<vector<int>> s(m);
    rep(i, m) {
        cin >> k[i];
        rep(j, k[i]) {
            int x; cin >> x, x--;
            s[i].push_back(x);
        }
    }
    vector<int> p(m);
    rep(i, m) cin >> p[i];

    int n2 = 1 << n, ans = 0;
    rep(i, n2) {
        int res = 0;
        rep(j, m) {
            int cnt = 0;
            rep(ki, k[j]) {
                if (i >> s[j][ki] & 1) cnt++;
            }
            if (cnt % 2 == p[j]) res++;
        }
        if (res == m) ans++;
    }
    cout << ans << endl;
}
