#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// ポイント
// sparseな既出管理はmapではなくsetで十分

const vector<int> dx = {2,1,-1,-2,-2,-1,1,2}, dy = {1,2,2,1,-1,-2,-2,-1};

int main() {
    int n, m; cin >> n >> m;
    vector<P> p(m);
    rep(i, m) {
        int a, b; cin >> a >> b, a--, b--;
        p[i] = {a, b};
    }

    set<P> st;
    rep(i, m) {
        st.insert(p[i]);
        rep(r, 8) {
            int nh = p[i].first + dx[r], nw = p[i].second + dy[r];
            if (nh < 0 || nh >= n || nw < 0 || nw >= n) continue;
            st.emplace(nh, nw);
        }
    }
    ll ans = ll(n) * n - st.size();
    cout << ans << endl;
}
