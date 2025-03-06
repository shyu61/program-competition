#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// lazysegtree

// 罠
// なし。非常に典型的なusecase

// ポイント
// 区間を扱う際は座標圧縮を検討する

template<typename T=int>
struct CC {
    bool initialized;
    vector<T> xs;

    CC(): initialized(false) {}
    void add(T x) { xs.push_back(x); }
    void init() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        initialized = true;
    }
    int size() {
        if (!initialized) init();
        return xs.size();
    }
    int operator()(T x) {
        if (!initialized) init();
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
};

template<typename T, auto op, T iv>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;
    vector<bool> flag;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<T>(n * 2 - 1, iv);
        lazy = vector<T>(n * 2 - 1);
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

// lazysegtreeによる解法
int main() {
    int w, n; cin >> w >> n;
    vector<int> ini(w + 1);
    LazySegtree<int, op, 0> seg(ini);

    rep(i, n) {
        int l, r; cin >> l >> r, l--;
        int h = seg.query(l, r) + 1;
        cout << h << '\n';
        seg.update(l, r, h);
    }
}

// lazysegtree + 座標圧縮による解法
int main() {
    int w, n; cin >> w >> n;
    vector<int> l(n), r(n);
    rep(i, n) cin >> l[i] >> r[i], l[i]--;

    CC cc;
    rep(i, n) { cc.add(l[i]); cc.add(r[i]); }
    rep(i, n) { l[i] = cc(l[i]); r[i] = cc(r[i]); }

    vector<int> ini(cc.size() + 1);
    LazySegtree<int, op, 0> seg(ini);

    rep(i, n) {
        int h = seg.query(l[i], r[i]) + 1;
        cout << h << '\n';
        seg.update(l[i], r[i], h);
    }
}

// 座標圧縮による解法
int main() {
    int w, n; cin >> w >> n;
    vector<int> l(n), r(n);
    rep(i, n) cin >> l[i] >> r[i], l[i]--;

    CC cc;
    rep(i, n) { cc.add(l[i]); cc.add(r[i]); }
    rep(i, n) { l[i] = cc(l[i]); r[i] = cc(r[i]); }

    vector<int> cnt(cc.size());
    rep(i, n) {
        int mv = 0;
        for (int j = l[i]; j < r[i]; j++) mv = max(mv, cnt[j]);
        mv++;
        for (int j = l[i]; j < r[i]; j++) cnt[j] = mv;
        cout << mv << '\n';
    }
}
