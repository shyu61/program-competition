#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep(i, n) a[i] = i + 1;

    int pos = 0;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int p, x; cin >> p >> x, p--;
            a[(pos + p) % n] = x;
        }
        if (type == 2) {
            int p; cin >> p, p--;
            cout << a[(pos + p) % n] << '\n';
        }
        if (type == 3) {
            int k; cin >> k;
            pos = (pos + k) % n;
        }
    }
}
