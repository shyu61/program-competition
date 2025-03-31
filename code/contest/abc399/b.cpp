#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// 配列の同じ値を集約したいケースでは頻度配列が使える

int main() {
    int n; cin >> n;
    vector<P> p(n);
    rep(i, n) {
        int x; cin >> x;
        p[i] = {x, i};
    }
    sort(p.rbegin(), p.rend());

    vector<int> ans(n);
    rep(i, n) {
        if (i == 0) ans[p[i].second] = 1;
        else if (p[i].first == p[i - 1].first) ans[p[i].second] = ans[p[i - 1].second];
        else ans[p[i].second] = i + 1;
    }

    rep(i, n) cout << ans[i] << '\n';
}

int main() {
    int n; cin >> n;
    vector<vector<int>> cnt(101);
    rep(i, n) {
        int p; cin >> p;
        cnt[p].push_back(i);
    }

    int r = 1;
    vector<int> ans(n);
    for (int i = 100; i >= 0; i--) {
        for (auto v : cnt[i]) ans[v] = r;
        r += cnt[i].size();
    }

    rep(i, n) cout << ans[i] << '\n';
}
