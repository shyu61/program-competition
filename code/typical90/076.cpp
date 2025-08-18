#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// 循環配列の区間問題は2倍列を考える

bool solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    ll sum = 0;
    rep(i, n) sum += a[i];
    if (sum % 10 != 0) return false;

    sum /= 10;
    a.insert(a.end(), a.begin(), a.end());

    int n2 = n * 2, pos = 0;
    ll cur = 0;
    rep(i, n) {
        while (pos < n2 && pos - i < n && cur < sum) cur += a[pos++];
        if (cur == sum) return true;
        cur -= a[i];
    }
    return false;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
