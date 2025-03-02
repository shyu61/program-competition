#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定アルゴリズム
// 射影

// トラップ
// swap: 代表値のswapと見れるか

// 方針
// 射影配列を用意して解くことを考える。愚直にはswapできないのでこの部分の高速化を考える
// 遅延評価を考えてみると、結局遅延評価する鳩を記録するのに同じ計算量がかかってしまう。
// 巣単位で記録しても、評価までに何度もswapが行われるとtrackしきれない。故に違うアプローチを考える。
// 何らかの代表値のみをswapさせたいとすると、箱にラベルをつけて、ラベルを張り替えることを考える。

int main() {
    int n, q; cin >> n >> q;

    vector<int> p2b(n), b2l(n), l2b(n);
    rep(i, n) {
        p2b[i] = i;  // pigeon_to_box
        b2l[i] = i;  // box_to_label
        l2b[i] = i;  // label_to_box
    }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int a, b; cin >> a >> b, a--, b--;
            p2b[a] = l2b[b];
        } else if (type == 2) {
            int a, b; cin >> a >> b, a--, b--;
            b2l[l2b[a]] = b;
            b2l[l2b[b]] = a;
            swap(l2b[a], l2b[b]);
        } else {
            int a; cin >> a, a--;
            int box = p2b[a];
            cout << b2l[box] + 1 << '\n';
        }
    }
}
