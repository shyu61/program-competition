#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    while (1) {
        int n, x; cin >> n >> x;
        if (n == 0 && x == 0) break;
        int ans = 0;
        rep(i, n) rep(j, i) rep(k, j) {
            if (i + j + k + 3 == x) ans++;
        }
        cout << ans << '\n';
    }
}
