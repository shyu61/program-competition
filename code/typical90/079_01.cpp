#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題。全探索は無理。操作に順序を規定できる類の問題は、操作の可換性をまず検討する。
// 可換性がある。故にセオリー通り自由度の低い位置から考えると、左上から順に処理すれば良いことがわかる。

// 🔷抑えるべき抽象論は？
// 組合せ最適化問題の方針
// - 選択に順序を規定できない(制約が飛び地など): グラフ,判定問題
// - 順序を規定できる
//   - 選択の最適性がその瞬間の状態のみで決定できる: 貪欲法
//   - 過去の選択に依存する: dp
//   - その他観点
//     - 操作の可換性
//     - 自由度の低い場所から決めていく

int main() {
    int h, w; cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> a[i][j];
    rep(i, h) rep(j, w) {
        int x; cin >> x;
        a[i][j] -= x;
    }

    ll ans = 0;
    rep(i, h - 1) rep(j, w - 1) {
        int val = a[i][j];
        if (val != 0) {
            ans += abs(val);
            a[i][j] -= val;
            a[i + 1][j] -= val;
            a[i][j + 1] -= val;
            a[i + 1][j + 1] -= val;
        }
    }

    rep(i, h) rep(j, w) {
        if (a[i][j] != 0) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes\n" << ans << endl;
}
