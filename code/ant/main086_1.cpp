// Binary Indexed Tree(A Simple Problem with Integers): p163
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// https://tsutaj.hatenablog.com/entry/2017/03/30/224339
// 遅延セグ木: ある区間全体の更新など、更新範囲が広い場合に処理を遅延させる手法
// 基本更新をループするとO(nlogn)かかるが、遅延させることで通常の更新と同様のコストO(logn)で処理できる

// セグ木を使いたいシーンにおいて、一括の更新が走るケースで使用を検討する

const ll INF = 1e14 + 1;
int sz = 1;
vector<int> a;
vector<ll> dat, lazy;

void init(int n) {
    while (sz < n) sz *= 2;
    dat = lazy = vector<ll>(sz * 2 - 1);
    a.resize(sz, 0);

    // 再帰使わなくても書ける
    for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
    for (int i = sz - 2; i >= 0; i--) {
        dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
}

// 遅延評価を行う
// トリガーはクエリ時と更新時(更新時も各ノードを参照するのでついでに評価して値配列に書き出しておく)
void eval(int id, int l, int r) {
    // 遅延配列が空でない場合、自分の更新と子への伝搬が起こる
    if (lazy[id] != 0) {
        dat[id] += lazy[id];

        if (r - l > 1) {
            lazy[id * 2 + 1] += lazy[id] / 2;
            lazy[id * 2 + 2] += lazy[id] / 2;
        }

        lazy[id] = 0;
    }
}

// [a,b)に対して+xする
void add(int a, int b, int x, int id, int l, int r) {
    eval(id, l, r);

    // 範囲外なら何もしない
    if (b <= l || r <= a) return;

    // 完全に被覆しているなら遅延配列に値を入れた後に評価
    if (a <= l && r <= b) {
        lazy[id] += (r - l) * x;
        eval(id, l, r);  // この区間の子への変更は遅延される
    } else {  // 一部区間を含んでいる場合は子を計算して値を貰ってくる
        add(a, b, x, id * 2 + 1, l, (l + r) / 2);
        add(a, b, x, id * 2 + 2, (l + r) / 2, r);
        dat[id] = dat[id * 2 + 1] + dat[id * 2 + 2];
    }
}

ll getsum(int a, int b, int id, int l, int r) {
    // 範囲外なら0
    if (b <= l || r <= a) return 0;

    eval(id, l, r);
    // 完全に被覆しているなら評価後の値を返す
    if (a <= l && r <= b) return dat[id];

    // 一部区間を含んでいる場合は子を計算して返却
    ll vl = getsum(a, b, id * 2 + 1, l, (l + r) / 2);
    ll vr = getsum(a, b, id * 2 + 2, (l + r) / 2, r);
    return vl + vr;
}

int main() {
    int N, Q; cin >> N >> Q;
    a = vector<int>(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    init(N);
    for (int i = 0; i < Q; i++) {
        char c; cin >> c;
        if (c == 'C') {
            int l, r, x; cin >> l >> r >> x;
            l--; r--;
            // [l,r]のすべての要素にxを加える
            add(l, r + 1, x, 0, 0, sz);
        } else {
            int l, r; cin >> l >> r;
            l--; r--;
            // [l,r]の和を求める
            cout << getsum(l, r + 1, 0, 0, sz) << endl;
        }
    }
}
