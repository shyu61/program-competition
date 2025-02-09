#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    vector<int> a(3);
    rep(i, 3) cin >> a[i];

    bool ok = false;
    if (a[0] * a[1] == a[2]) ok = true;
    if (a[1] * a[2] == a[0]) ok = true;
    if (a[2] * a[0] == a[1]) ok = true;

    cout << (ok ? "Yes" : "No") << endl;
}
