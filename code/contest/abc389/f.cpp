#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 逐次問題, 区間問題, クエリ問題

// 方針
// クエリ問題の方針は以下の2つ
// - オンライン高速化: 各クエリの処理を事前計算により高速化
// - オフライン高速化: クエリをソートなりして順番に処理することで累積構造などを使った高速化を図る
// 累積構造が使えなさそうなのでオンライン高速化を考える。

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

    // x以上(以下)となる最初の点
    int lower_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        eval(id, l, r);
        if (dat[id] != x && op(dat[id], x) == x) return -1;
        T vl = lower_bound(x, id * 2 + 1, l, (l + r) / 2);
        if (vl != -1) return vl;
        return lower_bound(x, id * 2 + 2, (l + r) / 2, r);
    }

    // xより大きく(小さく)なる最初の点
    int upper_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        eval(id, l, r);
        if (dat[id] == x || op(dat[id], x) == x) return -1;
        T vr = upper_bound(x, id * 2 + 2, (l + r) / 2, r);
        if (vr != -1) return vr;
        return upper_bound(x, id * 2 + 1, l, (l + r) / 2);
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

// segtree上で二分探索を行う場合
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

    for (int i = 0; i < n; i++) {
        int li = seg.lower_bound(l[i]), ri = seg.lower_bound(r[i]);
        seg.add(li, ri, 1);
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << seg.query(x, x + 1) << '\n';
    }
}

// 全てのXではなくQに存在する値のみでsegtreeを構築する解法
int main() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        r[i]++;
    }

    int q; cin >> q;
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        qs[i] = {x, i};
    }
    sort(qs.begin(), qs.end());

    vector<int> a(q);
    for (int i = 0; i < q; i++) a[i] = qs[i].first;
    LazySegtree<int, op, 0> seg(a);

    for (int i = 0; i < n; i++) {
        int li = seg.lower_bound(l[i]), ri = seg.lower_bound(r[i]);
        seg.add(li, ri, 1);
    }

    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        ans[qs[i].second] = seg.query(i, i + 1);
    }
    for (auto v : ans) cout << v << '\n';
}
