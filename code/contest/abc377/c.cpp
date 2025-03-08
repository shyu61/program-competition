#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

const vector<int> dx = {2,1,-1,-2,-2,-1,1,2}, dy = {1,2,2,1,-1,-2,-2,-1};

int main() {
    int n, m; cin >> n >> m;
    vector<P> p(m);
    rep(i, m) {
        int a, b; cin >> a >> b, a--, b--;
        p[i] = {a, b};
    }
    sort(p.begin(), p.end());

    map<P, bool> used;
    ll ans = ll(n) * n - m;
    rep(i, m) {
        // (a[i],b[i])が取れる範囲にある空きマスの数を数える
        int sum = 0;
        rep(r, 8) {
            int nh = p[i].first + dx[r], nw = p[i].second + dy[r];
            if (nh < 0 || nh >= n || nw < 0 || nw >= n) continue;
            P np = {nh, nw};
            int x = lower_bound(p.begin(), p.end(), np) - p.begin();
            if (x <= m && p[x] != np && !used[np]) {
                sum++;
                used[np] = true;
            }
        }
        ans -= sum;
    }
    cout << ans << endl;
}
