#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];
    int sum = 0;
    rep(i, n) sum += abs(a[i] - b[i]);
    k -= sum;
    if (k >= 0 && k % 2 == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}
