#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 切り上げ除算: ⌈x/d⌉=(x+d-1)/d

int main() {
    int n; cin >> n;
    vector<int> q(n), r(n);
    rep(i, n) cin >> q[i] >> r[i];
    int Q; cin >> Q;
    while (Q--) {
        int t, d; cin >> t >> d; t--;
        d -= r[t];
        int a = (d + q[t] - 1) / q[t];
        cout << a * q[t] + r[t] << '\n';
    }
}
