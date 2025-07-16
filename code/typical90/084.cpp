#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; string s; cin >> n >> s;

    vector<int> nx(n);
    {
        vector<int> pos(2, n);
        for (int i = n - 1; i >= 0; i--) {
            int id = s[i] == 'o' ? 1 : 0;
            nx[i] = pos[id ^ 1];
            pos[id] = i;
        }
    }

    ll ans = 0;
    for (auto v : nx) ans += n - v;
    cout << ans << endl;
}
