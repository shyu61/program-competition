// Mine Layer: p343
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// グリッド問題なので、全探索/貪欲法/DP/グラフ/stack を検討する -> グラフ化や状態遷移の記述が難しいので全探索が候補
// -> ナイーブにはO(2^RC)でいくら枝刈りできたとしてLargeは流石に間に合わなさそう -> 違う方法を考える必要がある
// -> 他に使ってない条件はないか？ -> 欲しいのは全マスの爆弾の組み合わせではなく「中央行の爆弾の総数」だけ。つまり最終的には行単位で分かれば十分
// -> 行単位での総数をカウントする方法はないか？ -> そもそも情報が自身と前後行の3つ分なので、この塊ごとに考える必要がありそう
// -> 累積和などと同様に、配列の各要素が連続した要素間で重複した情報を持つ場合は、適切にたし引きすることで重複を除去した値を取り出せるという性質を使うと、
//    3行まとまった情報から単一行の情報が抜き出せるのでは？と考える -> あとはセオリー通り1次元ずつ考えて適用すれば求解できる

// ポイント
// - 配列の各要素が連続した要素間で重複した情報を持つ場合は、適切にたし引きすることで重複を除去した値を取り出せる
// - 解けない時、まだ使ってない条件がないか考える
// - 2次元同時に考えるのが難しい時は、まず1次元で考えてみる

int R, C;
vector<vector<int>> field;

// サイズnの一次元版で総和を求める
int total(vector<int>& a, int n) {
    int res = 0;
    int s = n % 3 == 0 ? 1 : 0;
    for (int i = s; i < n; i += 3) res += a[i];
    return res;
}

// サイズnの一次元版で真ん中の値を求める
int center(vector<int>& a, int n) {
    int res = 0;
    if (n % 3 == 1 || n % 3 == 2) {
        int s = n % 3 == 1 ? 1 : 0;
        for (int i = s; i < n / 2; i += 3) {
            res += a[i];
            res += a[n - i - 1];
        }
        res = total(a, n) - res;
    } else {
        for (int i = 0; i < n / 2; i += 3) {
            res += a[i];
            res += a[n - i - 1];
        }
        res = res - total(a, n);
    }
    return res;
}

int main() {
    cin >> R >> C;
    field = vector<vector<int>>(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> field[i][j];
        }
    }

    vector<int> a(R);
    for (int i = 0; i < R; i++) {
        a[i] = total(field[i], C);
    }

    cout << center(a, R) << endl;
}
