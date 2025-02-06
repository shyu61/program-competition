#include <bits/stdc++.h>
using namespace std;

// BITは累積和のクエリと更新に特化した構造体で、セグ木の用途を限定し簡略化することでセグ木から定数倍の高速化を図ったもの
// 通常の累積和はクエリはO(1)だが、更新は全て再計算が必要で構築コストと同じO(n)かかる
// セグ木とBITは計算量は同じでクエリと更新がO(logn)、構築がO(n)である
// セグ木がtop-down的に再帰計算を行い、判定に範囲演算を行い、かつ必要ノードかどうかの判定を行うために使わないノードへのアクセスを行っているのに対して、
// BITはビット列を使うことで、予めアクセスするノードを知ることができ、オーバーヘッドがある再帰計算を避けつつ高速なビット演算のみで計算できるので、定数倍早い。

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
