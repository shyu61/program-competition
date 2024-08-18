// RMQ: Ranged Minimum Query
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6;
const int MAX_N = 1e5;
int dat[MAX_N * 2 - 1];

// 要素数
int n;

// segtreeの初期化
void init() {
    for (int i = 0; i < n * 2 - 1; i++) dat[i] = INF;
}

// k: k番目の値(ノード番号ではない), a: 更新値
void update(int k, int a) {
    // ノード番号に変換
    k += n - 1;
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
