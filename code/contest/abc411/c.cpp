#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// 配列外参照のチェックが必要な場合は、番兵の使用を検討する

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n + 2);
    int ans = 0;
    while (q--) {
        int t; cin >> t;
        if (a[t] == a[t - 1] && a[t] == a[t + 1]) ans++;
        if (a[t] != a[t - 1] && a[t] != a[t + 1]) ans--;
        a[t] ^= 1;
        cout << ans << '\n';
    }
}
