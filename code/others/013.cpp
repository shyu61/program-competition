// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F
// RMQ and RUQ
#include <bits/stdc++.h>
using namespace std;

template<auto op, int iv>
struct LazySegtree {
private:
    int n = 1;
    vector<int> dat, lazy;
    vector<bool> flag;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = lazy = vector<int>(n * 2 - 1, iv);
        flag = vector<bool>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (flag[id]) {
            dat[id] = lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] = lazy[id * 2 + 2] = lazy[id];
                flag[id * 2 + 1] = flag[id * 2 + 2] = true;
            }
            flag[id] = false;
        }
    }

    // [a,b)の値を全てxに変更
    void update(int a, int b, int x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] = x;
            flag[id] = true;
            eval(id, l, r);
        } else {
            update(a, b, x, id * 2 + 1, l, (l + r) / 2);
            update(a, b, x, id * 2 + 2, (l + r) / 2, r);
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }

    int query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        int vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
        int vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
        return op(vl, vr);
    }
};

int op(int a, int b) { return min(a, b); }

int main() {
    int n, q; cin >> n >> q;
    vector<int> A(n, INT_MAX);
    LazySegtree<op, INT_MAX> rmq(A);
    for (int i = 0; i < q; i++) {
        int a, s, t; cin >> a >> s >> t;
        if (a == 0) {
            int x; cin >> x;
            rmq.update(s, t + 1, x);
        } else {
            cout << rmq.query(s, t + 1) << '\n';
        }
    }
}
