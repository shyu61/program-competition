#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題なのでまず貪欲法を検討する。
// 明らかにdagなのでdpでも解けるが、結果を累積的にする必要がないので純粋な貪欲法で十分

int main() {
    int n; cin >> n;
    vector<int> c(n);
    for (int i = 1; i < n; i++) cin >> c[i];
    vector<bool> a(n);
    for (int i = 1; i < n; i++) {
        bool x; cin >> x;
        a[i] = x;
    }

    int ans = 0;
    for (int i = n - 1; i > 0; i--) {
        if (!a[i]) continue;
        int mv = n, mi = 0;
        for (int j = i - 1; j >= i - c[i]; j--) {
            if (a[j]) break;
            if (j - c[j] <= mv) {
                mv = j - c[j];
                mi = j;
            }
            if (j == i - c[i]) a[mi] = true;
        }
        ans++;
    }

    cout << ans << endl;
}
