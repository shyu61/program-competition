#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    vector<int> c(n);
    rep(i, n) c[i] = i + 1;

    int x = 0, y = 0, num = 0;
    do {
        if (c == a) x = num;
        if (c == b) y = num;
        num++;
    } while (next_permutation(c.begin(), c.end()));

    cout << abs(x - y) << endl;
}
