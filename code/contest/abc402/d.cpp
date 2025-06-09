#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷抑えるべき抽象論は？
// 対称な点は剰余で表現できる
// 全てに掛け算割り算をする場合は一意性は失われない
// - 中点などは1/2する必要がないこともしばしば

int main() {
    int n, m; cin >> n >> m;
    unordered_map<int, int> mp;
    rep(i, m) {
        int u, v; cin >> u >> v;
        int mid = (u + v) % n;
        mp[mid]++;
    }
    ll ans = ll(m) * (m - 1) / 2;
    for (auto [k, v] : mp) {
        if (v > 1) {
            ans -= ll(v) * (v - 1) / 2;
        }
    }
    cout << ans << endl;
}
