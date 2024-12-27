#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// まずは問題のジャンルを見抜く -> ビルkが見えるかどうかはビルi(i<k)しか関係ない。つまりは前から順番に見ていく逐次問題
// -> ナイーブに探索するとN(N+1)/2 = O(N^2)なので高速化を図りたい
// -> 遮るかどうかはxとhに依存つまり角度に依存しそうなのは直感的にわかる。min/maxの比較になりそうなのでスライド最小化と近しい考え方が使えそう
// -> 最も遮る可能性が高い候補のみ保持しておけばO(N)になる
// -> これを考えると直前のビルのみに依存して判定できることに気づく

// ポイント
// - 小数が絡む問題は式変形してなるべく小数計算する回数を減らす(ギリギリまで整数計算する)
// - indexではなく値の掛け算をするときは、overflowに注意する

int main(){
    int N; cin >> N;
    vector<ll> X(N), H(N);
    for (int i = 0; i < N; i++) cin >> X[i] >> H[i];

    bool all = true;
    double ans = -1;
    for (int i = 1; i < N; i++) {
        ll dx = X[i] - X[i - 1], dh = H[i] - H[i - 1];

        if (X[i - 1] * dh <= H[i - 1] * dx) all = false;

        ans = max(ans, double(X[i] * H[i - 1] - X[i - 1] * H[i]) / dx);
    }

    if (all) cout << -1 << endl;
    else cout << fixed << setprecision(10) << ans << endl;
}
