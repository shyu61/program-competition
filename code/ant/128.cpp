// Nim(Georgia and Bob): p278
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// Nimへの帰着を検討すべき問題
// - 組合せゲームかつ不偏ゲームである場合
//   - 確定性, 完全情報性, 零和, 有限, 操作対称性(同盤面ならプレイヤー間で行える操作に差異がない)
// - 公平ゲームである
//   - 同盤面ならプレイヤー間で行える操作に差異がない
// - 独立したサブゲームの集合から成る場合
// - 状態が減少する操作のみ許容され、有限回で決着する
//   - 増加操作を必ず相殺できる、操作が有限回に限られるなどの場合はその限りではない

int main() {
    int n; cin >> n;
    vector<int> p(n);
    rep(i, n) cin >> p[i];
    sort(p.begin(), p.end());

    int xo = 0;
    for (int i = 0; i < n - 1; i += 2) {
        // 2駒間の距離を石の数と考えてNimに帰着
        xo ^= (p[i + 1] - p[i] - 1);
    }
    if (n % 2 == 1) xo ^= p[0] - 1;

    if (xo != 0) cout << "Georgia will win" << endl;
    else cout << "Bob will win" << endl;
}
