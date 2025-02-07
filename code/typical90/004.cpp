#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int h, w; cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    rep(i, h) {
        rep(j, w) cin >> a[i][j];
    }

    vector<int> cols(w), rows(h);
    rep(i, h) {
        rep(j, w) rows[i] += a[i][j];
    }
    rep(i, w) {
        rep(j, h) cols[i] += a[j][i];
    }

    rep(i, h) {
        rep(j, w) {
            int ans = rows[i] + cols[j] - a[i][j];
            cout << ans << ' ';
        }
        cout << '\n';
    }
}
