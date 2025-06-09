#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, m; cin >> n >> m;
    vector<int> k(m);
    vector<vector<int>> a(n);
    rep(i, m) {
        cin >> k[i];
        rep(j, k[i]) {
            int x; cin >> x, x--;
            a[x].push_back(i);
        }
    }
    int ans = 0;
    rep(i, n) {
        int b; cin >> b, b--;
        for (auto v : a[b]) {
            if (--k[v] == 0) ans++;
        }
        cout << ans << '\n';
    }
}
