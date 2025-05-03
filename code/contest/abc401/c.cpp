#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷抑えるべき抽象論は？
// 剰余を取る時は、オーバーフローと負に注意する

const int M = 1e9;

int main() {
    int n, k; cin >> n >> k;
    if (k > n) {
        cout << 1 << endl;
        return 0;
    }

    vector<ll> a(n + 1);
    rep(i, k) a[i] = 1;

    a[k] = k;
    for (int i = k; i < n; i++) {
        a[i + 1] = 2 * a[i] - a[i - k] + M;
        a[i + 1] %= M;
    }

    cout << a[n] << endl;
}
