#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; cin >> n;
    string s, t; cin >> s >> t;
    int ans = 0;
    rep(i, n) {
        if (s[i] != t[i]) ans++;
    }
    cout << ans << endl;
}
