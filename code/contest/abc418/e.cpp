#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const ll INF = 1e7 + 1;

// pairをkeyとする配列は重い(mapやset)
// - 頻度配列ならvectorにしてsortして数えるのも手
// - pairを整数hash化するのも手
//   - (x + offset) * mx + (y + offset)
//   - mxの商がx, 剰余がyになる

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    bool operator<(const Point& p) const {
        if (x == p.x) return y < p.y;
        return x < p.x;
    }

    ll norm() { return x * x + y * y; }
};

int main() {
    int n; cin >> n;
    vector<Point> a(n);
    rep(i, n) cin >> a[i].x >> a[i].y;

    vector<Point> slopes, centers;
    rep(i, n) rep(j, i) {
        int dx = a[i].x - a[j].x;
        int dy = a[i].y - a[j].y;

        Point c = a[i] + a[j];

        centers.emplace_back(c);
        if (dx == 0) slopes.emplace_back(0, 1);
        else {
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }
            slopes.emplace_back(dx, dy);
        }
    }

    sort(slopes.begin(), slopes.end());
    sort(centers.begin(), centers.end());

    auto f = [&](vector<Point>& bk) {
        ll res = 0;
        int pos = 0;
        bk.emplace_back(INF, INF);
        rep(i, bk.size()) {
            if (bk[pos].x != bk[i].x || bk[pos].y != bk[i].y) {
                ll len = i - pos;
                res += len * (len - 1) / 2;
                pos = i;
            }
        }
        return res;
    };

    ll ans = f(slopes) - f(centers);
    cout << ans << endl;
}

int main() {
    int n; cin >> n;
    vector<Point> a(n);
    rep(i, n) cin >> a[i].x >> a[i].y;

    auto f = [&](int x, int y) -> ll {
        return (x + INF) * (INF * 2 + 1) + (y + INF);
    };

    unordered_map<ll, vector<ll>> mp;
    rep(i, n) rep(j, i) {
        int dx = a[i].x - a[j].x;
        int dy = a[i].y - a[j].y;

        ll key;
        if (dx == 0) key = f(0, 1);
        else {
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;
            // dxを正に揃える
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }
            key = f(dx, dy);
        }
        mp[key].push_back((a[i] - a[j]).norm());
    }

    ll ans = 0, cnt = 0;
    for (auto& [_, v] : mp) {
        ll m = v.size();
        ans += m * (m - 1) / 2;

        // 平行四辺形の数を数える
        unordered_map<int, ll> ump;
        for (auto vi : v) ump[vi]++;
        for (auto [ki, vi] : ump) {
            if (vi >= 2) cnt += vi * (vi - 1) / 2;
        }
    }
    ans -= cnt / 2;

    cout << ans << endl;
}
