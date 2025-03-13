#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 転倒数 → fenwick
// 初期状態からm回遷移をO(logn)以下で処理する方法を考えさせる問題 → 何らかの累積構造を使う

// 障壁
// k=0の転倒数の結果をk>0でどう使い回すかが鍵。剰余が0にならない限り転倒数は変化しないのはすぐ分かるので、
// 0になる時刻だけ考えればよく、その時に影響する要素の法則性を考えれば良い。
// 重要なのは0になる直前は常にその要素は配列内最大値をとっているということ。故に実は大小関係は考慮する必要がない。

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

    FenwickTree ft(m);
    ll cnt = 0;
    rep(i, n) {
        cnt += ft.sum(a[i] + 1, m);
        ft.add(a[i], 1);
    }

    // 周期が0に戻る時刻を計算
    vector<vector<int>> c(m + 1);
    rep(i, n) {
        c[m - a[i]].push_back(i);
    }

    rep(i, m) {
        if (c[i].size() == 0) {
            cout << cnt << '\n';
            continue;
        }
        int l = -c[i].size() + 1, r = -c[i].size() + 1;
        for (auto x: c[i]) {
            l += x;
            r += n - 1 - x;
        }
        cnt += l - r;
        cout << cnt << '\n';
    }
}
