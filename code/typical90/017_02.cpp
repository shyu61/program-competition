#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int INF = 1001001001;

struct Point {
    int s, t;
    bool operator<(const Point& other) const {
        if (s == other.s) return t < other.t;
        return s < other.s;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<Point> seg(m);
    rep(i, m) {
        int l, r; cin >> l >> r, l--, r--;
        seg[i] = Point{l, r};
    }
    sort(seg.begin(), seg.end());

    auto compT = [&](const Point& a, const Point& b) { return a.t < b.t; };

    // int n2 = sqrt(m);
    int n2 = 2300;  // √mlogm
    int bk_size = m / n2 + 1;
    vector<vector<Point>> bk(bk_size);
    rep(i, m) {
        bk[i / n2].push_back(seg[i]);
        if ((i + 1) % n2 == 0) {
            sort(bk[i / n2].begin(), bk[i / n2].end(), compT);
        }
    }
    sort(bk.back().begin(), bk.back().end(), compT);

    ll ans = 0;
    rep(i, m) {
        int s1 = seg[i].s, t1 = seg[i].t;
        // s1<s2
        auto it1 = upper_bound(seg.begin() + i + 1, seg.end(), Point{s1, INF});
        // s2<t1
        auto it2 = lower_bound(it1, seg.end(), Point{t1, 0});
        // t1<t2: segはsについてsortしているのでそのままでは二分探索できない
        // 代わりにtでsortしたbucketを使う
        ll res = 0;
        int l = it1 - seg.begin(), r = it2 - seg.begin();
        // 境界バケットを処理
        while (l < r && l % n2 != 0) {
            if (t1 < seg[l++].t) res++;
        }
        while (l < r && r % n2 != 0) {
            if (t1 < seg[--r].t) res++;
        }
        // 完全に含まれるバケットを処理
        while (l < r) {
            int j = l / n2;
            res += bk[j].end() - upper_bound(bk[j].begin(), bk[j].end(), Point{0, t1}, compT);
            l += n2;
        }
        ans += res;
    }
    cout << ans << endl;
}
