#include <bits/stdc++.h>
using namespace std;

template<auto op, int iv>
struct Segtree {
    vector<int> dat;
    int sz = 1;

    Segtree() {}
    // n: 要素数, a: 初期化時に利用する値
    Segtree(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<int>(sz * 2 - 1, iv);

        for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    int query(int a, int b) { return query(a, b, 0, 0, sz); }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = op(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    private:
        // [a, b)の最小値を探索
        // k: ノード番号, [l, r)はそれに紐づく区間
        int query(int a, int b, int k, int l, int r) {
            // [a, b)と[l, r)が交差しない場合は解なし
            if (b <= l || r <= a) return iv;
            // [a, b)が[l, r)を完全に含んでいる時、このノードの値が解
            if (a <= l && r <= b) return dat[k];
            else {
                int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
                int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
                return op(vl, vr);
            }
        }
};
