// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G
// RSQ and RAQ
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
};

int main() {
    int n, q; cin >> n >> q;
    vector<int> A(n);
    LazySegtree<ll> rsq(A);
    for (int i = 0; i < q; i++) {
        int a, s, t; cin >> a >> s >> t; s--;
        if (a == 0) {
            int x; cin >> x;
            rsq.add(s, t, x);
        } else {
            cout << rsq.query(s, t) << endl;
        }
    }
}
