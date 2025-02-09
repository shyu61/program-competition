#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, m; cin >> n >> m;
    vector<bool> ans(n + 1);
    rep(i, m) {
        int a; cin >> a;
        ans[a] = true;
    }

    cout << n - m << endl;
    for (int i = 1; i <= n; i++) {
        if (!ans[i]) cout << i << ' ';
    }
    cout << endl;
}
