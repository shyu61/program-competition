#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<P> edge;
    int ans = 0;
    rep(i, m) {
        int u, v; cin >> u >> v, u--, v--;
        if (u == v) ans++;
        else {
            if (v > u) swap(u, v);
            edge.emplace_back(u, v);
        }
    }

    sort(edge.begin(), edge.end());
    int x = edge.size();
    edge.erase(unique(edge.begin(), edge.end()), edge.end());
    ans += x - edge.size();
    cout << ans << endl;
}
