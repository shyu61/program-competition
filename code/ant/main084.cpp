// セグメント木を用いる問題: p156
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 逐次問題かつ、更新が自分より上すべてに毎回必要な問題
// 更新の高速化をしたい -> 区間更新 -> セグ木
// 座標系を分割する時は、それぞれはベクトルを持つと良い。結合処理が描きやすい。
// セグ木で重要なのは更新方法。どうやって回転を伝播させていくかを考える。

// RQMはsparse-tableでも実装できる。
// sparse-tableは更新が発生しないものに使える。
// セグ木よりメモリ効率が良くクエリはセグ木がO(logn)に対してO(loglogn)で動作するが、構築コストがセグ木がO(n)に対してO(nlogn)かかる

int N, C;
vector<double> L, vx, vy, vang;
ll sz = 1;

void init(int id, int left, int right) {
    vx[id] = vang[id] = 0.0;

    // 葉
    if (right - left == 1) {
        vy[id] = L[left];
    } else {
        int chl = id * 2 + 1; init(chl, left, (left + right) / 2);
        int chr = id * 2 + 2; init(chr, (left + right) / 2, right);
        vy[id] = vy[chl] + vy[chr];
    }
}

void change(int k, double a, int id, int left, int right) {
    if (left < k && k < right) {
        // 子を更新
        int chl = id * 2 + 1, chr = id * 2 + 2;
        int m = (left + right) / 2;
        change(k, a, chl, left, m);
        change(k, a, chr, m, right);

        // 自分を更新
        if (k <= m) vang[id] += a;
        vx[id] = vx[chl] + (-vy[chr] * sin(vang[id]) + vx[chr] * cos(vang[id]));
        vy[id] = vy[chl] + (vx[chr] * sin(vang[id]) + vy[chr] * cos(vang[id]));
    }
}

int main() {
    cin >> N >> C;
    L = vector<double>(N);
    vector<double> S(C), A(C), prv(N, M_PI);
    for (int i = 0; i < N; i++) cin >> L[i];
    for (int i = 0; i < C; i++) cin >> S[i] >> A[i];

    while (sz < N) sz *= 2;
    vx = vy = vang = vector<double>(sz * 2 - 1);
    init(0, 0, sz);

    for (int i = 0; i < C; i++) {
        int s = S[i];
        double a = A[i] / 180.0 * M_PI;

        change(s, a - prv[s], 0, 0, sz);
        prv[s] = a;
        cout << fixed << setprecision(2) << vx[0] << " " << vy[0] << endl;
    }
}
