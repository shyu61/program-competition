#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

// 関連問題: https://atcoder.jp/contests/abc189/tasks/abc189_e
// 一般的なアフィン変換を用いる解法

// アフィン変換: https://www.momoyama-usagi.com/entry/info-img05

struct AF {
    vector<vector<ll>> A;
    P t;
    AF() {
        A = vector<vector<ll>>(2, vector<ll>(2));
        t = {0, 0};
    }
};

AF mul(const AF& a, const AF& b) {
    AF res;
    rep(i, 2) rep(j, 2) rep(k, 2) {
        res.A[i][j] += a.A[i][k] * b.A[k][j];
    }
    ll t1 = a.A[0][0] * b.t.first + a.A[0][1] * b.t.second + a.t.first;
    ll t2 = a.A[1][0] * b.t.first + a.A[1][1] * b.t.second + a.t.second;
    res.t = {t1, t2};

    return res;
}

int main() {
    int n; cin >> n;
    vector<P> ps(n);
    rep(i, n) cin >> ps[i].first >> ps[i].second;

    int m; cin >> m;
    vector<AF> a(m + 1);
    a[0].A = {{1, 0}, {0, 1}};

    rep(i, m) {
        int type; cin >> type;
        AF cur;

        if (type == 1) cur.A = {{0, 1},{-1, 0}};
        if (type == 2) cur.A = {{0, -1},{1, 0}};
        if (type == 3) {
            int p; cin >> p;
            cur.A = {{-1, 0},{0, 1}};
            cur.t = {2 * p, 0};
        }
        if (type == 4) {
            int p; cin >> p;
            cur.A = {{1, 0},{0, -1}};
            cur.t = {0, 2 * p};
        }

        a[i + 1] = mul(cur, a[i]);
    }

    int q; cin >> q;
    while (q--) {
        int ai, bi; cin >> ai >> bi, bi--;
        auto [x, y] = ps[bi];
        auto& now = a[ai];

        ll nx = now.A[0][0] * x + now.A[0][1] * y + now.t.first;
        ll ny = now.A[1][0] * x + now.A[1][1] * y + now.t.second;

        cout << nx << ' ' << ny << '\n';
    }
}
