#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    double t, l, x, y; cin >> t >> l >> x >> y;
    int q; cin >> q;

    while (q--) {
        double e; cin >> e;
        double theta = e / t * 2 * M_PI;
        double sy = -l / 2 * sin(theta);
        double sz = -l / 2 * cos(theta) + l / 2;

        double dx = sqrt(x * x + (y - sy) * (y - sy));
        double dy = sz;
        cout << fixed << setprecision(8) << atan2(dy, dx) * 180 / M_PI << '\n';
    }
}
