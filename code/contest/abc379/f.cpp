#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using TP = tuple<int, int, int>;

// ジャンル
// クエリ問題, 逐次問題

// 方針
// この問題の最も重要な点は、「l,r両方から見えるビル」の条件を特定すること。
// かつ条件の場合は、どちらの方が条件的に厳しいかを考えると良い。
// 後ろからstackを使って逐次的に見ていけば、各ビルから見えるビルの個数はO(N)で求めることができる
// 鍵は単調性なのでstack+popが使えるというのは自然な発想
// 残りは区間をどう処理するか。lからもrからも見えるビルというのは、[l+1,r)で最後ビルから見えるビルの数に依存する
// 故に[l+1,r)で区間maxが高速にできれば良いので、segtreeを使えばいい
// 別解
// 後ろから逐次的に調べることができる時点で、クエリの順序最適化が使えるかもと想像できる
// 区間処理方法として、求めるものが「lから見えるビルのうちrより右にあるビルの個数」ということに気づければ
// 二分探索なりで求解できることに気づく。つまりはlからは見えるけど、rからは見えないビルは存在しないということ

// ポイント
// fenwickは個数管理に使える, 内部は位置配列を持っていると考えれば良い
//   - 二分探索する際は位置情報を要素の値として持ち、配列のindexが要素数を示すが、fenwickは位置情報はindexで、要素数は累積和として表現される
// stackやqueueで二分探索したい時はdequeを使う
// 単調性を作りたい場合はstack+popを使うと良い

template<auto op, int iv>
struct Segtree {
private:
    int n = 1;
    vector<P> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<P>(n * 2 - 1, {iv, -1});

        for (int i = 0; i < sz; i++) dat[i + n - 1] = {a[i], i};
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    P query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return {iv, -1};
        if (a <= l && r <= b) return dat[id];
        else {
            P vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            P vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }
};

P op(P& a, P& b) { return max(a, b); }

int main() {
    int n, q; cin >> n >> q;
    vector<int> h(n);
    rep(i, n) cin >> h[i];

    // 各ビルより後ろに高さが自身以上のビルがいくつあるか計算
    vector<int> a(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[i] > st.top()) st.pop();
        a[i] = st.size();
        st.push(h[i]);
    }

    Segtree<op, 0> rmq(h);

    while (q--) {
        int l, r; cin >> l >> r; l--;
        // ビルlは考慮しない
        int x = rmq.query(l + 1, r).second;
        cout << a[x] << '\n';
    }
}

// オフラインクエリで解く方法(二分探索)
int main() {
    int n, q; cin >> n >> q;
    vector<int> h(n);
    vector<vector<P>> qs(n);
    rep(i, n) cin >> h[i];
    rep(i, q) {
        int l, r; cin >> l >> r;
        qs[--l].emplace_back(r, i);
    }
    vector<int> ans(q);
    deque<P> deq;
    for (int i = n - 1; i >= 0; i--) {
        for (auto [r, j] : qs[i]) {
            int x = deq.end() - lower_bound(deq.begin(), deq.end(), make_pair(r, 0));
            ans[j] = x;
        }
        while (!deq.empty() && h[i] > deq.front().second) deq.pop_front();
        deq.emplace_front(i, h[i]);
    }

    for (auto x : ans) cout << x << '\n';
}

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

// オフラインクエリで解く方法(fenwick_tree)
int main() {
    int n, q; cin >> n >> q;
    vector<int> h(n);
    vector<vector<P>> qs(n);
    rep(i, n) cin >> h[i];
    rep(i, q) {
        int l, r; cin >> l >> r;
        qs[--l].emplace_back(r, i);
    }
    vector<int> ans(q);
    deque<P> deq;
    FenwickTree ft(n);
    for (int i = n - 1; i >= 0; i--) {
        for (auto [r, j] : qs[i]) {
            ans[j] = ft.sum(r, n);
        }
        while (!deq.empty() && h[i] > deq.front().second) {
            ft.add(deq.front().first, -1);
            deq.pop_front();
        }
        deq.emplace_front(i, h[i]);
        ft.add(i, 1);
    }

    for (auto x : ans) cout << x << '\n';
}
