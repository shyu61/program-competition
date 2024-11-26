// RMQ: Ranged Minimum Query
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6;
int sz;
vector<int> dat;

// segtreeの初期化
void init(int n, vector<int>& a) {
    while (sz < n) sz *= 2;
    dat = vector<int>(sz * 2 - 1);
    a.resize(sz, 0);

    for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
    for (int i = sz - 2; i >= 0; i--) {
        dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
}

// k: k番目の値(ノード番号ではない), a: 更新値
void update(int k, int a) {
    // ノード番号に変換
    k += sz - 1;
    dat[k] = a;
    while (k > 0) {
        k = (k - 1) / 2;
        dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
}

// [a, b)の最小値を探索
// k: ノード番号, [l, r)はそれに紐づく区間
int query(int a, int b, int k, int l, int r) {
    // [a, b)と[l, r)が交差しない場合は解なし
    if (b <= l || r <= a) return INF;

    // [a, b)が[l, r)を完全に含んでいる時、このノードの値が解
    if (a <= l && r <= b) return dat[k];
    else {
        int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(vl, vr);
    }
}
