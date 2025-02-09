#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 逐次問題, 区間更新

// 方針
// 更新により区間自体が変化するパターン

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
