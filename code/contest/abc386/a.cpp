#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    vector<int> a(4);
    rep(i, 4) cin >> a[i];
    sort(a.begin(), a.end());

    bool ok = false;
    if (a[0] == a[1] && a[1] == a[2] && a[2] != a[3]) ok = true;
    if (a[0] == a[1] && a[1] != a[2] && a[2] == a[3]) ok = true;
    if (a[0] != a[1] && a[1] == a[2] && a[2] == a[3]) ok = true;

    cout << (ok ? "Yes" : "No") << endl;
}
