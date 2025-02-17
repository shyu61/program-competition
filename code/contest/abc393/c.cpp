#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    set<P> edges;
    int ans = 0;
    rep(i, m) {
        int u, v; cin >> u >> v;
        if (u == v) {
            ans++;
            continue;
        }
        if (u > v) swap(u, v);
        if (edges.contains({u, v})) ans++;
        else edges.emplace(u, v);
    }
    cout << ans << endl;
}
