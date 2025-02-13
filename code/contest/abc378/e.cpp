#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 全ペア走査問題, 数論, 剰余

// 方針
// 累積和を使えば内側のΣ計算はO(1)でできる。問題は区間走査で、区間数は全ペア数と等しくO(n^2)
// つまり全ペア生成せずに求解するタイプの問題
// 数式問題なので、式変形して単一のΣにしか依存しない形に分解することを考える
// 累積和で表すとそのまま単一Σ依存に分解でき、mod部分は場合分けすれば良い

// ポイント
// 転倒数はfenwick-tree

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
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> s(n + 1);
    rep(i, n) s[i + 1] = (s[i] + a[i]) % m;

    ll ans = 0;
    rep(r, n) ans += s[r] * r;
    rep(l, n) ans -= s[l] * (n - l - 1);

    FenwickTree ft(n + 1);
    int cnt = 0;
    rep(i, n + 1) {
        cnt += ft.sum(0, i);
        ft.add(i, 1);
    }
    ans += cnt * m;
    cout << ans << endl;
}
