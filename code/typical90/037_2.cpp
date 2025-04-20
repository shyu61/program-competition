#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// クエリ問題なので各クエリ操作のボトルネックをまず特定する。
// (1)幼児の移動,(2)2つの幼稚園のmaxの更新,(3)全体のminの更新の3操作をO(logn)程度でできれば良いことがわかる。
// (3)は1つのsegtreeでできるし、(1)(2)はmaxについてupdateとdeleteが高速であれば良いのでsetでできる

template<auto op, int iv>
struct Segtree {
private:
    int n = 1;
    vector<int> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<int>(n * 2 - 1, iv);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    int query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        else {
            int vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    // 元の配列でindex=kの要素をxに更新
    void update(int k, int x) {
        int id = k + n - 1;  // ノード番号に変換
        dat[id] = x;
        while (id > 0) {
            id = (id - 1) / 2;
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }
};

int op(int a, int b) { return min(a, b); }

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i], b[i]--;

    const int m = 2e5;

    vector<multiset<int, greater<int>>> st(m);
    rep(i, n) st[b[i]].insert(a[i]);

    vector<int> ini(m, INF);
    rep(i, m) {
        if (st[i].size()) ini[i] = *st[i].begin();
    }
    Segtree<op, INF> seg(ini);

    while (q--) {
        // 幼児cを幼稚園dへ移動
        int c, to; cin >> c >> to, c--, to--;
        int from = b[c];
        b[c] = to;

        // add
        auto it = st[from].find(a[c]);
        st[to].insert(*it);
        seg.update(to, *st[to].begin());

        // erase
        st[from].erase(it);
        if (st[from].size()) seg.update(from, *st[from].begin());
        else seg.update(from, INF);

        seg.update(to, *st[to].begin());

        cout << seg.query(0, m + 1) << '\n';
    }
}
