#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

// 関連問題: https://atcoder.jp/contests/abc189/tasks/abc189_e

int main() {
    int n; cin >> n;
    vector<int> X(n), Y(n);
    rep(i, n) cin >> X[i] >> Y[i];

    int m; cin >> m;
    vector<P> org(m + 1), vec(m + 1);
    vec[0] = {1, 2};
    rep(i, m) {
        int type, p = 0; cin >> type;
        if (type > 2) cin >> p;

        auto [x, y] = org[i];
        auto [vx, vy] = vec[i];
        if (type == 1) {
            org[i + 1] = {y, -x};
            vec[i + 1] = {vy, -vx};
        }
        if (type == 2) {
            org[i + 1] = {-y, x};
            vec[i + 1] = {-vy, vx};
        }
        if (type == 3) {
            org[i + 1] = {x + (p - x) * 2, y};
            vec[i + 1] = {-vx, vy};
        }
        if (type == 4) {
            org[i + 1] = {x, y + (p - y) * 2};
            vec[i + 1] = {vx, -vy};
        }
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b, b--;
        auto [x, y] = org[a];
        auto [vx, vy] = vec[a];

        if (abs(vx) == 1) {
            vx *= X[b];
            vy = vy / 2 * Y[b];
        } else {
            vx = vx / 2 * Y[b];
            vy *= X[b];
        }

        cout << x + vx << ' ' << y + vy << '\n';
    }
}
