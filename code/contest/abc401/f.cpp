#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷初見でどうやったら解けるか
// 🔷抑えるべき抽象論は？
// 木における最遠点
// - 直径をなす2点どちらかとの距離になる
// 二分探索が使えるケースでは尺取り法もセットで検討する
// - 全ペアなどsortでき、単調性を導入できるケースでは使えることが多い

int main() {
    auto read = [&]() {
        int n; cin >> n;
        vector<vector<int>> g(n);
        rep(i, n - 1) {
            int u, v; cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> dist(n);
        auto dfs = [&](auto dfs, int v, int p = -1, int dep = 0) -> P {
            dist[v] = max(dist[v], dep);
            P res = {dep, v};
            for (auto u : g[v]) {
                if (u == p) continue;
                res = max(res, dfs(dfs, u, v, dep + 1));
            }
            return res;
        };
        int a = dfs(dfs, 0).second;
        auto [d,b] = dfs(dfs, a);
        dfs(dfs, b);

        return make_pair(d, dist);
    };

    auto [da, a] = read();
    auto [db, b] = read();
    int d = max(da, db);

    sort(a.rbegin(), a.rend());
    sort(b.begin(), b.end());

    int nb = b.size();

    vector<ll> s(nb + 1);
    rep(i, nb) s[i + 1] = s[i] + b[i];

    ll ans = 0; int pos = 0;
    for (auto ai : a) {
        while (pos < nb && b[pos] + ai + 1 <= d) pos++;
        ans += ll(d) * pos;
        ans += ll(ai + 1) * (nb - pos) + s[nb] - s[pos];
    }
    cout << ans << endl;
}
