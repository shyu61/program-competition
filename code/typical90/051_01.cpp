#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, int>;

// 🔷初見でどうやったら解けるか
// 数え上げ問題なのでまず全探索を考える。制約条件的に半分全列挙が行けそう。
// 半分全列挙は、片方は全探索しつつ、もう一方は単調性を利用して二分探索や尺取り法をするのが典型。
// 価格はそれでできるが、個数の制約チェックを同時に行う必要がある。
// 尺取りをベースに価格が条件内に入るものをfenwick-treeで管理して、個数をindexとして管理すれば解ける

// 単調性を使った高速な探索をしたい値が2種類(a,b)ある場合
// - aかbのどちらかの閾値が狭い場合
//   - 頻度配列を使う: 閾値が狭い方をindexとして定義し、もう一方をそのindexごとにsortした配列として持つ
//   - fenwick-treeを使う: 閾値が狭い方をindexとして個数をftに持つ。尺取りしつつ範囲外に出たものはft上での個数減算を行う

int main() {
    int n, k; ll p; cin >> n >> k >> p;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    auto f = [&](int n2, int offset = 0) {
        vector<vector<ll>> c(n + 1);
        rep(i, 1 << n2) {
            ll sum = 0; int cnt = 0;
            rep(s, n2) {
                if (i >> s & 1) {
                    sum += a[s + offset];
                    cnt++;
                }
            }
            c[cnt].push_back(sum);
        }
        rep(i, n + 1) sort(c[i].begin(), c[i].end());
        return c;
    };
    int n2 = n / 2;
    auto c1 = f(n2);
    auto c2 = f(n - n2, n2);

    ll ans = 0;
    rep(i, k + 1) {
        auto& c = c2[k - i];
        if (c.size() == 0) continue;
        int pos = c.size() - 1;
        for (auto v : c1[i]) {
            while (pos >= 0 && v + c[pos] > p) pos--;
            if (pos < 0) break;
            ans += pos + 1;
        }
    }
    cout << ans << endl;
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

int main() {
    int n, k; ll p; cin >> n >> k >> p;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    auto f = [&](int n2, int offset = 0) {
        vector<P> c;
        rep(i, 1 << n2) {
            ll sum = 0; int cnt = 0;
            rep(s, n2) {
                if (i >> s & 1) {
                    sum += a[s + offset];
                    cnt++;
                }
            }
            c.emplace_back(sum, cnt);
        }
        sort(c.begin(), c.end());
        return c;
    };
    int n2 = n / 2;
    auto c1 = f(n2);
    auto c2 = f(n - n2, n2);

    FenwickTree ft(n + 1);
    for (auto [_, cnt] : c2) ft.add(cnt, 1);

    ll ans = 0; int pos = c2.size() - 1;
    for (auto [v, cnt] : c1) {
        while (pos >= 0 && v + c2[pos].first > p) {
            ft.add(c2[pos].second, -1);
            pos--;
        }
        if (pos < 0) break;
        if (cnt > k) continue;
        ans += ft.sum(k - cnt, k - cnt + 1);
    }

    cout << ans << endl;
}
