#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 逐次問題, 区間更新

// 方針
// 更新により区間自体が変化するパターン

// ポイント
// 逆順に考えた方が良いケースもある
// fenwick_treeは動的な累積和管理を行うデータ構造で、純粋な累積和管理以外にも「順序統計」を扱いたいケースでよく使われる
//   - nodeに頻度を持たせることで、「位置pは前から何番目か」や、二分探索と組み合わせて「前からx番目の位置はどこか」などを高速に処理できる

template <typename T=int>
struct FenwickTree {
    vector<T> bit;
    const T n;
    FenwickTree(T n_) : bit(n_ + 1, 0), n(n_) {};

    void add(int i, T x) {
        assert(0 <= i && i < n);
        i++;
        while (i <= n) {
            bit[i - 1] += x;
            i += i & -i;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }

    private:
        T sum(int i) {
            T s = 0;
            while (i > 0) {
                s += bit[i - 1];
                i -= i & -i;
            }
            return s;
        }
};

// fenwicktreeでの解法
int main() {
    int n; cin >> n;
    vector<int> p(n);
    rep(i, n) cin >> p[i];

    // ans配列の空席のうち、前からi番目の場所がどこか
    // fenwicktreeで持っておくと、位置からそこが前から何番目かがわかる
    // 二分探索を使えば前からi番目の場所の位置がわかる

    FenwickTree ft(n);
    rep(i, n) ft.add(i, 1);

    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {

        auto is_ok = [&](int mid) -> bool {
            return ft.sum(0, mid + 1) >= p[i];
        };

        // 前からp[i]番目の空席となる位置を探索
        // ft.sum()がp[i]以上となる最小の点
        int ok = n - 1, ng = -1;
        while (ok - ng > 1) {
            int mid = (ok + ng) / 2;
            is_ok(mid) ? ok = mid : ng = mid;
        }
        ans[ok] = i + 1;
        ft.add(ok, -1);
    }

    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

template<typename T>
struct Segtree {
private:
    int n = 1;
    vector<int> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<int>(n * 2 - 1, 0);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }

    int query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return dat[id];
        else {
            int vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }

    // 元の配列でindex=kの要素をxに更新
    void update(int k, int x) {
        int id = k + n - 1;  // ノード番号に変換
        dat[id] = x;
        while (id > 0) {
            id = (id - 1) / 2;
            dat[id] = dat[id * 2 + 1] + dat[id * 2 + 2];
        }
    }

    // x以上となる最初の点
    int lower_bound(T x, T sum = 0, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] + sum < x) return n;
        T vl = lower_bound(x, sum, id * 2 + 1, l, (l + r) / 2);
        if (vl != n) return vl;
        return lower_bound(x, sum + dat[id * 2 + 1], id * 2 + 2, (l + r) / 2, r);
    }

    // xより大きくなる最初の点
    int upper_bound(T x, T sum = 0, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] + sum <= x) return n;
        T vr = upper_bound(x, sum + dat[id * 2 + 1], id * 2 + 2, (l + r) / 2, r);
        if (vr != n) return vr;
        return upper_bound(x, sum, id * 2 + 1, l, (l + r) / 2);
    }
};

// segtree上での二分探索を利用した解法
int main() {
    int n; cin >> n;
    vector<int> p(n);
    rep(i, n) cin >> p[i];

    Segtree<int> rsq(vector<int>(n, 1));
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        int x = rsq.lower_bound(p[i]);
        ans[x] = i + 1;
        rsq.update(x, 0);
    }

    rep(i, n) cout << ans[i] << ' ';
    cout << endl;
}
