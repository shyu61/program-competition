// 反転(Face The Right Way): p139
#include <bits/stdc++.h>
using namespace std;

// 反転の問題のポイント
// 1. 同じ要素を2回操作することは無駄 -> 端から見た時にすでに前のものは、もう見る必要がない
// 2. 操作の順序は結果に影響を与えない -> 整理しやすい順に処理をする(本問題の場合は端から)
// 3. 反転操作は反転回数の偶奇のみに影響することから、逐一反転せずとも反転回数を記憶してき一括で判定することで計算量を抑えられる

// 逐次問題において、影響が累積的な部分を特定することは非常に有効
// 累積的であれば実に多くの計算効率化方法が存在する。本問題も累積和と同じ発想を使っている。

int n;
vector<int> a;

int inversion(int k) {
    int sum = 0, cnt = 0;
    vector<int> f(n);
    for (int i = 0; i + k <= n; i++) {
        // すでに前を向いている場合はskip
        if ((a[i] + sum) % 2 == 0) {
            // [i,i+k)の牛を反転
            f[i] = 1;
            sum += f[i];
            cnt++;
        }
        if (i - k + 1 >= 0) sum -= f[i - k + 1];
    }

    // 残りの範囲の牛をチェック
    // 後ろを向いている牛が1頭でもいれば-1を返却
    for (int i = n - k + 1; i < n; i++) {
        if ((a[i] + sum) % 2 == 0) return -1;
        if (i - k + 1 >= 0) sum -= f[i - k + 1];
    }
    return cnt;
}

int main() {
    cin >> n;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        char s; cin >> s;
        a[i] = s == 'F' ? 1 : 0;
    }

    int K = 1, M = n;
    // ここを二分探索にすることはできない。
    // 優先して求めたいのは最小のMであってKではないので、Kは全て調べる必要がある
    for (int k = 1; k <= n; k++) {
        int cnt = inversion(k);
        if (cnt != -1 && cnt < M) {
            K = k;
            M = cnt;
        }
    }
    cout << K << " " << M << endl;
}
