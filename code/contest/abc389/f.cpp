#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 逐次問題, 区間問題, クエリ問題

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

int op(int a, int b) { return max(a, b); }

int main() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        r[i]++;
    }

    const int XMAX = 5e5 + 1;
    vector<int> a(XMAX + 1);
    for (int i = 0; i <= XMAX; i++) a[i] = i;
    LazySegtree<int, op, 0> seg(a);

    auto lwb = [&](int t) {
        int lb = 0, ub = XMAX + 1;
        while (ub - lb > 1) {
            int mid = (lb + ub) / 2;
            int x = seg.query(lb, mid);
            (x < t) ? lb = mid : ub = mid;
        }
        return lb;
    };

    for (int i = 0; i < n; i++) {
        seg.add(lwb(l[i]), lwb(r[i]), 1);
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << seg.query(x, x + 1) << '\n';
    }
}
