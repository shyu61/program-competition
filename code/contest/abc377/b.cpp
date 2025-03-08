#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int m = 8;
    vector<string> mas(m);
    rep(i, m) cin >> mas[i];

    int ans = 0;
    rep(i, m) rep(j, m) {
        if (mas[i][j] == '#') continue;
        bool ok = true;
        rep(k, m) {
            if (mas[i][k] == '#') ok = false;
            if (mas[k][j] == '#') ok = false;
        }
        if (ok) ans++;
    }
    cout << ans << endl;
}
