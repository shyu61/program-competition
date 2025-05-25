#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

template<typename T, auto op, T iv>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
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
    void add(int a, int b, int x, int id = 0, int l = 0, int r = -1) {
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

int op(int a, int b) { return min(a, b); }

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int n2 = n * 2;
        ll ans = 0;
        vector<P> a(n2);
        rep(i, n2) {
            int v; cin >> v;
            a[i] = {v, i};
            ans += v;
        }

        vector<int> ini(n2);
        rep(i, n2) ini[i] = i + 1;
        LazySegtree<int, op, INF> seg(ini);
        sort(a.begin(), a.end());

        int cnt = 0;
        for (auto [v, ix] : a) {
            if (cnt == n) break;
            if (seg.query(ix, ix + 1) > 1 && seg.query(ix, n2) > 1) {
                seg.add(ix, n2, -2);
                ans -= v;
                cnt++;
            }
        }
        cout << ans << '\n';
    }
}
