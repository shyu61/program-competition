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

// BITの本質は、セグ木を累積和に特化させることで常に1からの区間だけを考えればよいシンプルな形に帰着させたことである。
// 常に1からの区間だけ考えれば良いので、各ノードの右の子は全て不要になる。故に各階層のノード数は1/2になり、現れる頻度は半分になる。
// 故に、最下層は2^1ごとにノードが現れ、1つ上は2^2ごと、高さhの階層は2^hごとにノードが現れる。これをビット列で考えると階層の高さとビットの桁が一致することになる。
// この性質を利用して各ノードへのアクセスがルートから辿るのではなくインデックスアクセスできるようになって、セグ木より高速になる。
// sumが常に最下位ビットを見れば良いのは、オフセットを逆順で辿っていく(自分より上の階層で、かつ自分より左の区間をカバーするノードを辿る)ことになり、それはやがて0へと帰着するからである。
// 数字におけるある桁以下というのは、そのある桁までをオフセットとした小区間の繰り返しと捉えるとBITの構造が捉えやすい。

// 注意点はBITはもはや木ではないということ。加えて、クエリは左へ伝播し、更新は右へ伝播するイメージを持っておくこと。更新が右へ伝播する理由は、ある地点への更新は、その地点を含む区間に影響するので、
// その区間を含むのはそれより右側の区間を表現するノードのみであるため。

// i&-iが最下位ビットを表す理由だが、-iはiの補数表現であり、反転して+1している。反転した状態では最下位ビットより下の位は全て1になっている。そこに+1すると、
// それらの位は全て繰り上がり反転して0になっている最下ビットの位置に1が立つ。それより上の位には影響はないので0のままになる。

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