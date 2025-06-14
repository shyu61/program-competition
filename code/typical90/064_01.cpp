#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const ll INF = 1000000000000000000LL;  // 1e18

template<typename T, auto op, T iv>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;

public:
    LazySegtree() {}
    LazySegtree(const vector<T>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<T>(n * 2 - 1, iv);
        lazy = vector<T>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (lazy[id] != 0) {
            dat[id] += lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] += lazy[id];
                lazy[id * 2 + 2] += lazy[id];
            }
            lazy[id] = 0;
        }
    }

    // [a,b)の値を全てxに変更
    void add(int a, int b, T x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] = x;
            eval(id, l, r);
        } else {
            add(a, b, x, id * 2 + 1, l, (l + r) / 2);
            add(a, b, x, id * 2 + 2, (l + r) / 2, r);
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }

    T query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        T vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
        return op(vl, vr);
    }
};

ll op(ll a, ll b) { return max(a, b); }

int main() {
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    ll ans = 0;
    rep(i, n - 1) ans += abs(a[i + 1] - a[i]);

    LazySegtree<ll, op, -INF> seg(a);

    rep(i, q) {
        int l, r, v; cin >> l >> r >> v, l--;
        ll pre = 0;
        if (l > 0) pre += abs(seg.query(l - 1, l) - seg.query(l, l + 1));
        if (r < n) pre += abs(seg.query(r - 1, r) - seg.query(r, r + 1));

        seg.add(l, r, v);

        ll now = 0;
        if (l > 0) now += abs(seg.query(l - 1, l) - seg.query(l, l + 1));
        if (r < n) now += abs(seg.query(r - 1, r) - seg.query(r, r + 1));

        ans += now - pre;
        cout << ans << '\n';
    }
}
