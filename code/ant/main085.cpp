// Binary Indexed Tree(バブルソートの交換回数): p162
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BIT {
    vector<T> bit;
    const T n;
    BIT(T n_) : bit(n_ + 1, 0), n(n_) {};

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    };

    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    };
};

// バブルソートのswap回数 -> 自分より左にある自分より大きい数の個数 -> 左から順に個数を区間ごとに数え上げる
// 自分より大きい数の個数 = 自身の番号 - 自分の数までの個数

// 思考フロー
// 自分より左にある自分より大きい数の個数を求めたい -> 各要素を左から順に見るとき、同じ要素を要素を何度も見てる
// -> 累積的に考えると高速化できそう -> 欲しいのは自分の値より大きい数の個数なので、値ごとに個数を保持しておけば良い
// さらに欲しいのは、値ごとの個数じゃなく、ある値以上（以下）の個数 -> 個数に対して累積和を取れば良い
// -> 動的なのでセグ木かBITで実装すればOK

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    BIT<ll> bit(n);

    ll ans = 0;
    // O(nlogn)
    for (int i = 0; i < n; i++) {
        ans += i - bit.sum(a[i]);
        bit.add(a[i], 1);
    }
    cout << ans << endl;
}
