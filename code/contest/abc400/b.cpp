#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 抑えるべき抽象論
// ループやΣにおいて、和や積で積み上がっていくような値は累積値として使い回す

// 類問
// 区間の伸長, Σ1/n^iなど
// 尺取り法が絡むケースも多い

int main() {
    int n, m; cin >> n >> m;
    ll ans = 1, res = 1;
    rep(i, m) {
        res *= n;
        if (res > 1e9) {
            cout << "inf" << endl;
            return 0;
        }
        ans += res;
    }

    if (ans > 1e9) cout << "inf" << endl;
    else cout << ans << endl;
}
