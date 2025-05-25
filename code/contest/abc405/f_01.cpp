#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using TP = tuple<int, int, int>;

// 🔷抑えるべき抽象論は？
// いもす法
// - 基本用途は領域加算で、領域の重なりをカウントする。最後に1回累積話和をとる。
// - 重なりだけじゃなく、交差や包含など、特定条件の重なりも表現できる。
//   - 端点の更新を工夫することによって表現する。
//   - クエリが動的で、条件が動的に変化する場合は、毎回累積和を取る代わりにfenwick-treeなどので高速に処理する。

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

bool comp(P& a, P& b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

bool comp2(TP& a, TP& b) {
    if (get<1>(a) == get<1>(b)) return get<0>(a) < get<0>(b);
    return get<1>(a) < get<1>(b);
}

int main() {
    int n, m; cin >> n >> m;
    vector<P> s(m);
    rep(i, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        s[i] = {a, b};
    }
    sort(s.begin(), s.end(), comp);

    int q; cin >> q;
    vector<TP> t(q);
    rep(i, q) {
        int c, d; cin >> c >> d;
        c--, d--;
        t[i] = {c, d, i};
    }
    sort(t.begin(), t.end(), comp2);

    FenwickTree ft(n * 2);
    // d<∀bとして初期化
    for (auto [a, b] : s) ft.add(a, 1);

    int pos = 0;
    vector<int> ans(q);
    for (auto [c, d, i] : t) {
        // b<dとなる線分について更新
        while (pos < m && s[pos].second < d) {
            ft.add(s[pos].first, -2);
            ft.add(s[pos].second, 1);
            pos++;
        }
        ans[i] = ft.sum(c, d + 1);
    }

    rep(i, q) cout << ans[i] << '\n';
}
