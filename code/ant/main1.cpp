// セグメント木
#include <bits/stdc++.h>
using namespace std;

const int ST_SIZE = (1 << 15) - 1;
const int MAX_N = 1e4;
const int MAX_C = 1e4;

int N, C;
int L[MAX_N];
int S[MAX_C], A[MAX_N];

// セグメント木のデータ
double vx[ST_SIZE], vy[ST_SIZE];
double ang[ST_SIZE];

// 現在の角度
double prv[MAX_N];

// セグメント木の初期化
// k: 要素番号, l,r: 区間
void init(int k, int l, int r) {
    ang[k] = vx[k] = 0.0;

    // 区間が1ということは葉、つまり先端
    if (r - l == 1) {
        vy[k] = L[l];
    } else {
        int chl = k * 2 + 1, chr = k * 2 + 2;
        init(chl, l, (l + r) / 2);
        init(chr, (l + r) / 2, r);
        // 初期状態ではただ垂直方向に積み上がっているだけなので足すだけ
        vy[k] = vy[chl] + vy[chr];
    }
}

// k: 要素番号, a: 角度, v: ノード番号, l,r: 区間
void change(int k, double a, int v, int l, int r) {
    if (l < k && k < r) {
        int chl = v * 2 + 1, chr = v * 2 + 2;
        int m = (l + r) / 2;
        // 再帰処理により子から更新される
        change(k, a, chl, l, m);
        change(k, a, chr, m, r);
        // 左の区間の回転は右の区間全てに影響を及ぼす
        if (k <= m) ang[v] += a;

        double s = sin(ang[v]), c = cos(ang[v]);
        vx[v] = vx[chl] + (c * vx[chr] - s * vy[chr]);
        vy[v] = vy[chl] + (s * vx[chr] + c * vy[chr]);
    }
}

int main() {
    cin >> N >> C;
    for (int i = 0; i < N; i++) cin >> L[i];
    for (int i = 0; i < C; i++) {
        cin >> S[i] >> A[i];
    }

    // 初期化
    init(0, 0, N);
    for (int i = 0; i < N; i++) prv[i] = M_PI;

    // 各クエリを処理
    for (int i = 0; i < C; i++) {
        int s = S[i];
        double a = A[i] / 360.0 * 2 * M_PI;

        change(s, a - prv[s], 0, 0, N);
        prv[s] = a;

        cout << fixed << setprecision(2) << vx[0] << " " << vy[0] << endl;
    }
}
