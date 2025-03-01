#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

const int n = 8;

int main() {
    int k; cin >> k;
    vector<int> x(k), y(k);
    rep(i, k) cin >> x[i] >> y[i];

    vector<int> a(n);
    rep(i, n) a[i] = i;

    do {
        bool skip = false;
        rep(i, k) {
            if (a[x[i]] != y[i]) skip = true;
        }
        if (skip) continue;
        bool ok = true;
        rep(i, n) rep(j, i) {
            int left = a[i] - (i - j), right = a[i] + (i - j);
            if (left >= 0 && a[j] == left) ok = false;
            if (right < n && a[j] == right) ok = false;
        }
        if (ok) {
            rep(i, n) {
                rep(j, n) cout << (a[i] == j ? 'Q' : '.');
                cout << '\n';
            }
            return 0;
        }
    } while (next_permutation(a.begin(), a.end()));
}
