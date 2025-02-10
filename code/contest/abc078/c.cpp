#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 期待値

// 方針
// 遷移を伴うが、各状態での確率は等しいのでdpを使う必要はなさそう
// WAの場合というのはいわゆる自己遷移になる。つまり、E=p*1+(1-p)(E+1) <=> E=1/p である

// ポイント
// 一般に、「確率pで成功するミッションを成功するまでトライし続けたとき、トライ回数の期待値は1/pである」
//   - 自己遷移を考えれば簡単に証明できる

int main() {
    int n, m; cin >> n >> m;
    int cost = 1900 * m + 100 * (n - m);
    int cnt = 1;
    rep(i, m) cnt *= 2;

    cout << cost * cnt << endl;
}
