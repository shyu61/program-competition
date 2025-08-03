#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 数え上げ+片方固定の問題

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // i+a[i] = j-a[j]
    unordered_map<int, int> mp;
    rep(i, n) mp[i - a[i]]++;

    ll ans = 0;
    rep(i, n) {
        mp[i - a[i]]--;
        int x = i + a[i];
        ans += mp[x];
    }
    cout << ans << endl;
}
