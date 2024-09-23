// デックの利用: スライド最小値: p300
// seg木での解法
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;
int n, k;
vector<int> a, dat;

void init(int v, int l, int r) {
    // 終了判定
    if (r - l == 1) dat[v] = a[l];
    else {
        // 子へ移動
        int chl = v * 2 + 1;
        int chr = v * 2 + 2;
        init(chl, l, (l + r) / 2);
        init(chr, (l + r) / 2, r);

        // 帰りがけに値を格納していく
        dat[v] = min(dat[chl], dat[chr]);
    }
}

// [a, b)を探索
int query(int a, int b, int v, int l, int r) {
    // 終了条件
    if (b <= l || r <= a) return INF;
    if (a <= l && r <= b) return dat[v];

    // 子へ移動
    int vall = query(a, b, v * 2 + 1, l, (l + r) / 2);
    int valr = query(a, b, v * 2 + 2, (l + r) / 2, r);
    return min(vall, valr);
}

int main() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // seg木
    dat = vector<int>(n * 2 - 1);
    init(0, 0, n);

    for (int i = 0; i <= n - k; i++) {
        cout << query(i, i + k, 0, 0, n) << " ";
    }
    cout << endl;
}
