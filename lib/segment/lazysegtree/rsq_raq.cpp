#include <bits/stdc++.h>
using namespace std;

// 区間和 x RAQ
template<typename T>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = lazy = vector<T>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (lazy[id] != 0) {
            dat[id] += lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] += lazy[id] / 2;
                lazy[id * 2 + 2] += lazy[id] / 2;
            }
            lazy[id] = 0;
        }
    }

    // [a,b)に対して+x
    void add(int a, int b, int x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] += (r - l) * x;
            eval(id, l, r);
        } else {
            add(a, b, x, id * 2 + 1, l, (l + r) / 2);
            add(a, b, x, id * 2 + 2, (l + r) / 2, r);
            dat[id] = dat[id * 2 + 1] + dat[id * 2 + 2];
        }
    }

    T query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return dat[id];
        T vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
        return vl + vr;
    }

    // x以上(以下)となる最初の点
    int lower_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        eval(id, l, r);
        if (dat[id] < x) return n;
        T vl = lower_bound(x, id * 2 + 1, l, (l + r) / 2);
        if (vl != n) return vl;
        return lower_bound(x, id * 2 + 2, (l + r) / 2, r);
    }

    // xより大きく(小さく)なる最初の点
    int upper_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        eval(id, l, r);
        if (dat[id] <= x) return n;
        T vr = upper_bound(x, id * 2 + 2, (l + r) / 2, r);
        if (vr != n) return vr;
        return upper_bound(x, id * 2 + 1, l, (l + r) / 2);
    }
};
