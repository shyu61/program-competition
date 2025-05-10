#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const ll INF = 1000000000000000000LL;  // 1e18

// 🔷初見でどうやったら解けるか
// 組合せ最適化なので全探索から検討するのがセオリー
// 🔷抑えるべき抽象論は？
// 3進数全探索
// - k桁目を取り出す方法: s/3(k-1)%3
//   - 商はk桁目を右シフトし一桁目に降ろす操作で、剰余はその一桁目の数を取り出す操作
// - 一般にn進数のk桁目を取り出す方法: s/n^(k-1)%n

// 再帰による全探索
int main() {
    int n, m; cin >> n >> m;
    vector<int> c(n);
    rep(i, n) cin >> c[i];
    vector<vector<int>> a(m), zoo(n);
    rep(i, m) {
        int k; cin >> k;
        rep(j, k) {
            int x; cin >> x; x--;
            a[i].push_back(x);
            zoo[x].push_back(i);
        }
    }

    ll ans = INF;
    vector<int> cnt(m);
    auto dfs = [&](auto dfs, int dep, ll res) -> void {
        if (dep == n) {
            rep(i, m) {
                if (cnt[i] < 2) return;
            }
            ans = min(ans, res);
            return;
        }
        dfs(dfs, dep + 1, res);

        for (auto x : zoo[dep]) cnt[x]++;
        dfs(dfs, dep + 1, res + c[dep]);
        for (auto x : zoo[dep]) cnt[x]--;

        for (auto x : zoo[dep]) cnt[x] += 2;
        dfs(dfs, dep + 1, res + c[dep] * 2);
        for (auto x : zoo[dep]) cnt[x] -= 2;
    };

    dfs(dfs, 0, 0LL);

    cout << ans << endl;
}

// 3進数による全探索
int main() {
    int n, m; cin >> n >> m;
    vector<int> c(n);
    rep(i, n) cin >> c[i];
    vector<vector<int>> zoo(n);
    rep(i, m) {
        int k; cin >> k;
        rep(j, k) {
            int x; cin >> x; x--;
            zoo[x].push_back(i);
        }
    }

    vector<int> po(n + 1, 1);
    rep(i, n) po[i + 1] = po[i] * 3;

    ll ans = INF;
    rep(s, po[n]) {
        ll cost = 0;
        vector<int> cnt(m);
        rep(i, n) {
            int x = s / po[i] % 3;
            for (auto j : zoo[i]) cnt[j] += x;
            cost += x * c[i];
        }
        bool ok = true;
        rep(i, m) {
            if (cnt[i] < 2) {
                ok = false;
                break;
            }
        }
        if (ok) ans = min(ans, cost);
    }

    cout << ans << endl;
}
