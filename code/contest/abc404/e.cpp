#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// TODO

int main() {
    int n; cin >> n;
    vector<int> c(n - 1);
    vector<bool> a(n - 1);
    rep(i, n - 1) cin >> c[i];
    rep(i, n - 1) {
        int x; cin >> x;
        if (x > 0) a[i] = true;
    }

    int ans = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (!a[i]) continue;

        int mv = 0, mi = 0;
        int exist = -1;
        for (int j = i - 1; j >= max(0, i - c[i]); j--) {
            if (a[j]) exist = j;
            int d = i - j + c[j];
            if (d >= mv) {
                mv = d;
                mi = j;
            }
        }
        for (int j = i + 1; j >= min(n - 1, i + c[i]); j++) {
            if (a[j]) exist = j;
            int d = j - i + c[j];
            if (d >= mv) {
                mv = d;
                mi = j;
            }
        }

        if (exist == -1) a[mi] = true;
        a[i] = false;
        ans++;
    }

    cout << ans << endl;
}
