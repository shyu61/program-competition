#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    unordered_map<int, int> is;
    vector<int> b(n);
    rep(i, n) {
        if (is.contains(a[i])) b[i] = is[a[i]];
        else b[i] = -1;
        is[a[i]] = i + 1;
    }

    rep(i, n) cout << b[i] << ' ';
    cout << endl;
}
