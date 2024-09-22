// 貪欲法: 硬貨の問題
// p42
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> r{1,5,10,50,100,500};

int main() {
    int a, n = 6;
    vector<int> c(n);
    cin >> c[0] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> a;

    ll ans = 0;
    for (int i = n - 1; i >= 0 && a > 0; i--) {
        int q = min(a / r[i], c[i]);
        a -= r[i] * q;
        ans += q;
    }

    cout << ans << endl;
}
