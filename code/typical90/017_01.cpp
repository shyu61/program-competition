#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// ジャンル
// 数え上げ, 計算幾何

int main() {
    int n, m; cin >> n >> m;
    vector<P> s(m);
    rep(i, m) {
        int l, r; cin >> l >> r, l--, r--;
        s[i] = {l, r};
    }
    sort(s.begin(), s.end());

    int ans = 0;
    rep(i, m) {
        // Ls<Lt
        int p1 = upper_bound(s.begin(), s.end(), make_pair(s[i].first, INF)) - s.begin();
        // Lt<Rs
        int p2 = lower_bound(s.begin() + p1, s.end(), make_pair(s[i].second, 0)) - s.begin();
        // Rs<Rt
        for (int j = p1; j < p2; j++) {
            if (s[i].second < s[j].second) ans++;
        }
    }
    cout << ans << endl;
}
