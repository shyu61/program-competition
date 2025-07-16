#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// next配列を使った解法
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

// ランレングス圧縮を使った解法
int main() {
    int n; string s; cin >> n >> s;
    s += '#';  // 番兵

    vector<int> a;
    int l = 0;
    rep(i, n) {
        if (s[i] != s[i + 1]) {
            a.push_back(i - l + 1);
            l = i + 1;
        }
    }

    ll ans = ll(n) * (n + 1) / 2;
    for (auto i : a) ans -= ll(i) * (i + 1) / 2;
    cout << ans << endl;
}
