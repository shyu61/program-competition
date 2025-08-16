#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// パリティの類問
// https://atcoder.jp/contests/abc086/tasks/arc089_a

int main() {
    int n; cin >> n;
    n++;
    vector<int> t(n), x(n), y(n);
    for (int i = 1; i < n; i++) cin >> t[i] >> x[i] >> y[i];

    for (int i = 1; i < n; i++) {
        int dt = t[i] - t[i - 1], dx = x[i] - x[i - 1], dy = y[i] - y[i - 1];
        int d = abs(dx) + abs(dy);
        if (dt < d || (dt - d) % 2 != 0) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
}
