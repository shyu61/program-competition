#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int h, w; cin >> h >> w;
    vector<vector<int>> mas(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> mas[i][j];

    int ans = 0;
    int n2 = 1 << h;
    rep(s, n2) {
        vector<vector<int>> g = mas;
        rep(i, h) {
            if (s >> i & 1) {
                rep(j, w) g[i][j] = !g[i][j];
            }
        }
        int res = 0;
        rep(j, w) {
            int sum = 0;
            rep(i, h) sum += g[i][j];
            res += max(sum, h - sum);
        }
        ans = max(ans, res);
    }
    cout << ans << endl;
}
