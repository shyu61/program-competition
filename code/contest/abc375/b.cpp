#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> x(n + 2), y(n + 2);
    rep(i, n) cin >> x[i + 1] >> y[i + 1];
    x[0] = x[n + 1] = 0;
    y[0] = y[n + 1] = 0;

    double ans = 0;
    rep(i, n + 1) {
        ll dx = x[i] - x[i + 1];
        ll dy = y[i] - y[i + 1];
        ans += sqrt(dx * dx + dy * dy);
    }
    cout << fixed << setprecision(8) << ans << endl;
}
