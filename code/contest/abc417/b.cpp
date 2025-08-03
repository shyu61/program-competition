#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    rep(i, m) {
        int b; cin >> b;
        rep(j, n) {
            if (a[j] == b) {
                a[j] = -1;
                break;
            }
        }
    }

    rep(i, n) {
        if (a[i] != -1) cout << a[i] << " ";
    }
}
