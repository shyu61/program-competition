#include <bits/stdc++.h>
using namespace std;

// BITは累積和のクエリと更新に特化した構造体で、セグ木の用途を限定し簡略化することでセグ木から定数倍の高速化を図ったもの
// 通常の累積和はクエリはO(1)だが、更新は全て再計算が必要で構築コストと同じO(n)かかる
// セグ木とBITは計算量は同じでクエリと更新がO(logn)、構築がO(n)である
// セグ木がtop-down的に再帰計算を行い、判定に範囲演算を行い、かつ必要ノードかどうかの判定を行うために使わないノードへのアクセスを行っているのに対して、
// BITはビット列を使うことで、予めアクセスするノードを知ることができ、オーバーヘッドがある再帰計算を避けつつ高速なビット演算のみで計算できるので、定数倍早い。

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
