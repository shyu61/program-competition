#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    ll a; int b, c; cin >> a >> b >> c;
    ll x = 1;
    rep(i, b) x *= c;
    if (a < x) cout << "Yes" << endl;
    else cout << "No" << endl;
}
