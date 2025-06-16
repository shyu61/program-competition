#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep(i, q) {
        int x; cin >> x, x--;
        if (x >= 0) {
            a[x]++;
            cout << x + 1 << ' ';
        } else {
            int mn = INF, mi = -1;
            rep(j, n) {
                if (a[j] < mn) {
                    mn = a[j];
                    mi = j;
                }
            }
            a[mi]++;
            cout << mi + 1 << ' ';
        }
    }
    cout << endl;
}
