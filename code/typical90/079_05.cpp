#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// https://atcoder.jp/contests/agc023/tasks/agc023_a

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> s(n + 1);
    rep(i, n) s[i + 1] = s[i] + a[i];

    ll ans = 0;
    unordered_map<ll, int> mp;
    rep(i, n + 1) {
        ans += mp[s[i]];
        mp[s[i]]++;
    }
    cout << ans << endl;
}
